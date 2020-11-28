#include "base/performance_daemon.h"
#include "base/fftype.h"
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;
using namespace ff;

PerformanceDaemon_t::PerformanceDaemon_t():
m_started(false),
m_timeout_sec(3600),
m_timer_service(NULL)
{
}

PerformanceDaemon_t::~PerformanceDaemon_t()
{
    stop();
    if (m_timer_service)
    {
        delete m_timer_service;
        m_timer_service = NULL;
    }
}


int PerformanceDaemon_t::start(const string& path_, int seconds_)
{
    if (true == m_started) return -1;
    
    m_path = path_;
    int rc = ::access(m_path.c_str(), F_OK);
    if (0 != rc)
    {
        rc = MKDIR(m_path.c_str());
        if (rc != 0)
        {
            printf("PerformanceDaemon_t::start mkdir<%s>failed error<%s>\n", m_path.c_str(), ::strerror(errno));
            return -1;
        }
    }
    
    m_timeout_sec = seconds_;
    
    //! 启动定时器 1 times/seconds
    m_timer_service = new TimerService(&m_task_queue, 1000);
    
    m_started = true; //! timer will start
    
    struct lambda_t
    {
        static void run(void* p_)
        {
            ((PerformanceDaemon_t*)p_)->run();
        }
    };

    m_thread.create_thread(Task(&lambda_t::run, this), 1);
    return 0;
}

int PerformanceDaemon_t::stop()
{
    if (false == m_started) return -1;
    
    if (m_timer_service)
    {
    	m_timer_service->stop();
    }
    
    m_started = false; //! timer will stop
    
    m_task_queue.close();
    m_thread.join();
    return 0;
}

void PerformanceDaemon_t::post(const string& mod_, long arg_, long us_)
{
    if (m_started)
    {
        m_task_queue.produce(TaskBinder::gen(&PerformanceDaemon_t::add_perf_data, this, mod_, arg_, us_));
    }
    else
    {
        this->start("perf", 60*10);
    }
}

void PerformanceDaemon_t::handle_timer()
{
    flush();
    //m_perf_info.clear();
    if (m_timer_service)
	    m_timer_service->timerCallback(m_timeout_sec * 1000, Task(&timer_lambda_t::setup_timer, this));
}

void PerformanceDaemon_t::flush()
{
    map<string, perf_info_t>::iterator it = m_perf_info.begin();
    
    time_t timep   = time(NULL);
    struct tm *tmp = localtime(&timep);
    
    char tmp_buff[256] = {0};
    char buff[1024]    = {0};
    
    sprintf(tmp_buff, "/%04d-%02d-%02d.perf",
            tmp->tm_year + 1900, tmp->tm_mon + 1, tmp->tm_mday);
    string filename = m_path + tmp_buff;
    
    FILE* fp = ::fopen(filename.c_str(), "a+");
    if (NULL == fp)
    {
        return;
    }

    if(getc(fp) == EOF)
    {           
        int n = snprintf(buff, sizeof(buff), "time,mod,rps,exe_times,max_cost[us],min_cost[us],per_cost[us]\n");
        fwrite(buff, n, 1, fp);
    }

    sprintf(tmp_buff, "%04d%02d%02d-%02d:%02d:%02d",
            tmp->tm_year + 1900, tmp->tm_mon + 1, tmp->tm_mday,
            tmp->tm_hour, tmp->tm_min, tmp->tm_sec);
    for (; it != m_perf_info.end(); ++it)
    {
        perf_info_t& pinfo = it->second;
        long per = (pinfo.times == 0? 0: (pinfo.total / pinfo.times));
        long rps = (per == 0? 0: 1000000 / per);
        
        //! -------------------------- time, mod, max, min, per, rps, times
        int n = snprintf(buff, sizeof(buff), "%s,%s,%ld,%ld,%ld,%ld,%ld\n",
                 tmp_buff, it->first.c_str(), rps, pinfo.times, pinfo.max, per == 0? 0: pinfo.min, per);
        fwrite(buff, n, 1, fp);
        pinfo.clear();
    }
    fclose(fp);
    
    
    sprintf(tmp_buff, "/%04d-%02d-%02d.counter",
            tmp->tm_year + 1900, tmp->tm_mon + 1, tmp->tm_mday);
    string filecounter = m_path + tmp_buff;
    Singleton<ObjSumMgr>::instance().dump(filecounter);
}



void PerformanceDaemon_t::run()
{
    m_timer_service->timerCallback(m_timeout_sec * 1000, Task(&timer_lambda_t::setup_timer, this));
    m_task_queue.run();
}

void PerformanceDaemon_t::add_perf_data(const string& mod_, long arg_, long us_)
{
    perf_info_t* pinfo = NULL;
    if (arg_ >= 0)
    {
        char msg[32];
        snprintf(msg, sizeof(msg), "%s[%ld]", mod_.c_str(), arg_);
        pinfo = &(m_perf_info[msg]);
    }
    else
    {
        pinfo = &(m_perf_info[mod_]);
    }
    
    pinfo->total += us_;
    pinfo->times += 1;
    
    if (us_ > pinfo->max)
    {
        pinfo->max = us_;
    }
    if (us_ < pinfo->min)
    {
        pinfo->min = us_;
    }
}
