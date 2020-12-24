
//脚本

#include "./ffworker_python.h"
#include "base/performance_daemon.h"
#include "server/http_mgr.h"
#ifdef _POSIX_C_SOURCE
#undef _POSIX_C_SOURCE
#endif
#ifdef _XOPEN_SOURCE
#undef _XOPEN_SOURCE
#endif
#include "python/ffpython.h"
#include "server/script.h"
using namespace ff;
using namespace std;


FFWorkerPython::FFWorkerPython():
    m_enable_call(true), m_started(false)
{
    m_ffpython = new ffpython_t();
}
FFWorkerPython::~FFWorkerPython()
{
    delete m_ffpython;
    m_ffpython = NULL;
}
static void py_send_msg_session(const userid_t& session_id_, uint16_t cmd_, const string& data_)
{
    Singleton<FFWorkerPython>::instance().sessionSendMsg(session_id_, cmd_, data_);
}
static void py_broadcast_msg_gate(uint16_t cmd_, const string& data_)
{
    Singleton<FFWorkerPython>::instance().gateBroadcastMsg(cmd_, data_);
}
static void py_multicast_msg_session(const vector<userid_t>& session_id_, uint16_t cmd_, const string& data_)
{
    Singleton<FFWorkerPython>::instance().sessionMulticastMsg(session_id_, cmd_, data_);
}
static void py_closeSession(const userid_t& session_id_)
{
    Singleton<FFWorkerPython>::instance().sessionClose(session_id_);
}
static void py_change_session_worker(const userid_t& session_id_, int to_worker_index_, string extra_data)
{
    Singleton<FFWorkerPython>::instance().sessionChangeWorker(session_id_, to_worker_index_, extra_data);
}
static string py_getSessionGate(const userid_t& session_id_)
{
    return Singleton<FFWorkerPython>::instance().getSessionGate(session_id_);
}
static string py_getSessionIp(const userid_t& session_id_)
{
    return Singleton<FFWorkerPython>::instance().getSessionIp(session_id_);
}
//! 判断某个service是否存在
static bool py_isExist(const string& service_name_)
{
    return Singleton<FFWorkerPython>::instance().getRpc().isExist(service_name_);
}
static string py_reload(const string& name_)
{
    return Singleton<FFWorkerPython>::instance().reload(name_);
}
static void py_log(int level, const string& mod_, const string& content_)
{
    Singleton<FFWorkerPython>::instance().pylog(level, mod_, content_);
}
static void py_writeLockGuard(){
    Singleton<FFWorkerPython>::instance().getSharedMem().writeLockGuard();
}
static bool py_regTimer(int mstimeout_, PyObject* pFuncSrc)
{
    struct lambda_cb
    {
        static void callback(PyObject* pFunc)
        {
            if (pFunc == NULL)
                return;
            try
            {
                Singleton<FFWorkerPython>::instance().get_ffpython().call_lambda<void>(pFunc);
            }
            catch(exception& e_)
            {
                LOGERROR((FFWORKER_PYTHON, "ffscene_python_t::py_onceTimer exception<%s>", e_.what()));
            }
            Py_XDECREF(pFunc);
        }
    };
    
    if (pFuncSrc != NULL)
    {
        Py_INCREF(pFuncSrc);
    }
        
    Singleton<FFWorkerPython>::instance().regTimer(mstimeout_, 
                TaskBinder::gen(&lambda_cb::callback, pFuncSrc));
    return true;
}
//!数据库相关操作
static long py_connectDB(const string& host_, const string& group_)
{
    return DB_MGR_OBJ.connectDB(host_, group_);
}
static void py_asyncQuery(long db_id_,const string& sql_, PyObject* pFuncArg)
{
    struct lambda_cb: public FFSlot::FFCallBack
    {
        lambda_cb(PyObject* pFuncSrc):pFunc(pFuncSrc){}
        virtual void exe(FFSlot::CallBackArg* args_)
        {
            if (NULL == pFunc)
            {
                return;
            }
            if (args_->type() != TYPEID(DbMgr::queryDBResult_t))
            {
                return;
            }
            DbMgr::queryDBResult_t* data = (DbMgr::queryDBResult_t*)args_;

            Singleton<FFWorkerPython>::instance().getRpc().get_tq().produce(TaskBinder::gen(&lambda_cb::call_python, pFunc,
                                                                   data->errinfo, data->result_data, data->col_names, data->affectedRows));
        }
        static void call_python(PyObject* pFuncSrc, string errinfo, vector<vector<string> > ret_, vector<string> col_, int affectedRows)
        {
            if (pFuncSrc == NULL)
            {
                return;
            }
            
            PyObject* pyRet = PyDict_New();
            {
                string key = "datas";
                PyObject *k = pytype_traits_t<string>::pyobj_from_cppobj(key);
                PyObject *v = pytype_traits_t<vector<vector<string> > >::pyobj_from_cppobj(ret_);
                PyDict_SetItem(pyRet, k, v);
                Py_DECREF(k);
                Py_DECREF(v);
            }
            {
                string key = "fields";
                PyObject *k = pytype_traits_t<string>::pyobj_from_cppobj(key);
                PyObject *v = pytype_traits_t<vector<string> >::pyobj_from_cppobj(col_);
                PyDict_SetItem(pyRet, k, v);
                Py_DECREF(k);
                Py_DECREF(v);
            }
            {
                string key = "errinfo";
                PyObject *k = pytype_traits_t<string>::pyobj_from_cppobj(key);
                PyObject *v = pytype_traits_t<string>::pyobj_from_cppobj(errinfo);
                PyDict_SetItem(pyRet, k, v);
                Py_DECREF(k);
                Py_DECREF(v);
            }
            {
                string key = "affectedRows";
                PyObject *k = pytype_traits_t<string>::pyobj_from_cppobj(key);
                PyObject *v = pytype_traits_t<int>::pyobj_from_cppobj(affectedRows);
                PyDict_SetItem(pyRet, k, v);
                Py_DECREF(k);
                Py_DECREF(v);
            }
            try
            {
                if (Singleton<FFWorkerPython>::instance().m_enable_call)
                {
                    Singleton<FFWorkerPython>::instance().get_ffpython().call_lambda<void>(pFuncSrc, pyRet);
                }
            }
            catch(exception& e_)
            {
                LOGERROR((FFWORKER_PYTHON, "workerobj_python_t::gen_queryDB_callback exception<%s>", e_.what()));
            }
            Py_XDECREF(pFuncSrc);
            Py_DECREF(pyRet);
        }
        virtual FFSlot::FFCallBack* fork() { return new lambda_cb(pFunc); }
        PyObject*          pFunc;
    };
    
    if (pFuncArg != NULL)
    {
        Py_INCREF(pFuncArg);
    }
    DB_MGR_OBJ.queryDB(db_id_, sql_,  new lambda_cb(pFuncArg));
}
static void py_asyncQueryGroupMod(const string& group_, int mod_, const string& sql_, PyObject* pFuncArg)
{
    struct lambda_cb: public FFSlot::FFCallBack
    {
        lambda_cb(PyObject* pFuncSrc):pFunc(pFuncSrc){}
        virtual void exe(FFSlot::CallBackArg* args_)
        {
            if (NULL == pFunc)
            {
                return;
            }
            if (args_->type() != TYPEID(DbMgr::queryDBResult_t))
            {
                return;
            }
            DbMgr::queryDBResult_t* data = (DbMgr::queryDBResult_t*)args_;

            Singleton<FFWorkerPython>::instance().getRpc().get_tq().produce(TaskBinder::gen(&lambda_cb::call_python, pFunc,
                                                                   data->errinfo, data->result_data, data->col_names, data->affectedRows));
        }
        static void call_python(PyObject* pFuncSrc, string errinfo, vector<vector<string> > ret_, vector<string> col_, int affectedRows)
        {
            if (pFuncSrc == NULL)
            {
                return;
            }
            
            PyObject* pyRet = PyDict_New();
            {
                string key = "datas";
                PyObject *k = pytype_traits_t<string>::pyobj_from_cppobj(key);
                PyObject *v = pytype_traits_t<vector<vector<string> > >::pyobj_from_cppobj(ret_);
                PyDict_SetItem(pyRet, k, v);
                Py_DECREF(k);
                Py_DECREF(v);
            }
            {
                string key = "fields";
                PyObject *k = pytype_traits_t<string>::pyobj_from_cppobj(key);
                PyObject *v = pytype_traits_t<vector<string> >::pyobj_from_cppobj(col_);
                PyDict_SetItem(pyRet, k, v);
                Py_DECREF(k);
                Py_DECREF(v);
            }
            {
                string key = "errinfo";
                PyObject *k = pytype_traits_t<string>::pyobj_from_cppobj(key);
                PyObject *v = pytype_traits_t<string>::pyobj_from_cppobj(errinfo);
                PyDict_SetItem(pyRet, k, v);
                Py_DECREF(k);
                Py_DECREF(v);
            }
            {
                string key = "affectedRows";
                PyObject *k = pytype_traits_t<string>::pyobj_from_cppobj(key);
                PyObject *v = pytype_traits_t<int>::pyobj_from_cppobj(affectedRows);
                PyDict_SetItem(pyRet, k, v);
                Py_DECREF(k);
                Py_DECREF(v);
            }
            try
            {
                if (Singleton<FFWorkerPython>::instance().m_enable_call)
                {
                    Singleton<FFWorkerPython>::instance().get_ffpython().call_lambda<void>(pFuncSrc, pyRet);
                }
            }
            catch(exception& e_)
            {
                LOGERROR((FFWORKER_PYTHON, "workerobj_python_t::gen_queryDB_callback exception<%s>", e_.what()));
            }
            Py_XDECREF(pFuncSrc);
            Py_DECREF(pyRet);
        }
        virtual FFSlot::FFCallBack* fork() { return new lambda_cb(pFunc); }
        PyObject*          pFunc;
    };
    
    if (pFuncArg != NULL)
    {
        Py_INCREF(pFuncArg);
    }
    DB_MGR_OBJ.queryDBGroupMod(group_, mod_, sql_, new lambda_cb(pFuncArg));
}

static PyObject* py_query(long db_id_,const string& sql_)
{
    PyObject* pyRet = PyDict_New();
    string errinfo;
    vector<vector<string> > retdata;
    vector<string> col;
    int affectedRows = 0;
    DB_MGR_OBJ.syncQueryDB(db_id_, sql_, retdata, col, errinfo, affectedRows);
    
    {
        string key = "datas";
        PyObject *k = pytype_traits_t<string>::pyobj_from_cppobj(key);
        PyObject *v = pytype_traits_t<vector<vector<string> > >::pyobj_from_cppobj(retdata);
        PyDict_SetItem(pyRet, k, v);
        Py_DECREF(k);
        Py_DECREF(v);
    }
    {
        string key = "fields";
        PyObject *k = pytype_traits_t<string>::pyobj_from_cppobj(key);
        PyObject *v = pytype_traits_t<vector<string> >::pyobj_from_cppobj(col);
        PyDict_SetItem(pyRet, k, v);
        Py_DECREF(k);
        Py_DECREF(v);
    }
    {
        string key = "errinfo";
        PyObject *k = pytype_traits_t<string>::pyobj_from_cppobj(key);
        PyObject *v = pytype_traits_t<string>::pyobj_from_cppobj(errinfo);
        PyDict_SetItem(pyRet, k, v);
        Py_DECREF(k);
        Py_DECREF(v);
    }
    {
        string key = "affectedRows";
        PyObject *k = pytype_traits_t<string>::pyobj_from_cppobj(key);
        PyObject *v = pytype_traits_t<int>::pyobj_from_cppobj(affectedRows);
        PyDict_SetItem(pyRet, k, v);
        Py_DECREF(k);
        Py_DECREF(v);
    }
    return pyRet;
}

static PyObject* py_queryGroupMod(const string& group_, int mod_,const string& sql_)
{
    PyObject* pyRet = PyDict_New();
    string errinfo;
    vector<vector<string> > retdata;
    vector<string> col;
    int affectedRows = 0;
    DB_MGR_OBJ.syncQueryDBGroupMod(group_, mod_, sql_, retdata, col, errinfo, affectedRows);
    
    {
        string key = "datas";
        PyObject *k = pytype_traits_t<string>::pyobj_from_cppobj(key);
        PyObject *v = pytype_traits_t<vector<vector<string> > >::pyobj_from_cppobj(retdata);
        PyDict_SetItem(pyRet, k, v);
        Py_DECREF(k);
        Py_DECREF(v);
    }
    {
        string key = "fields";
        PyObject *k = pytype_traits_t<string>::pyobj_from_cppobj(key);
        PyObject *v = pytype_traits_t<vector<string> >::pyobj_from_cppobj(col);
        PyDict_SetItem(pyRet, k, v);
        Py_DECREF(k);
        Py_DECREF(v);
    }
    {
        string key = "errinfo";
        PyObject *k = pytype_traits_t<string>::pyobj_from_cppobj(key);
        PyObject *v = pytype_traits_t<string>::pyobj_from_cppobj(errinfo);
        PyDict_SetItem(pyRet, k, v);
        Py_DECREF(k);
        Py_DECREF(v);
    }
    {
        string key = "affectedRows";
        PyObject *k = pytype_traits_t<string>::pyobj_from_cppobj(key);
        PyObject *v = pytype_traits_t<int>::pyobj_from_cppobj(affectedRows);
        PyDict_SetItem(pyRet, k, v);
        Py_DECREF(k);
        Py_DECREF(v);
    }
    return pyRet;
}
//!调用其他worker的接口 
static void py_workerRPC(int workerindex, uint16_t cmd, const string& argdata, PyObject* pFuncArg){
    
    struct lambda_cb: public FFSlot::FFCallBack
    {
        lambda_cb(PyObject* pFuncArg):pFunc(pFuncArg){}
        virtual void exe(FFSlot::CallBackArg* args_)
        {
            if (Singleton<FFWorkerPython>::instance().m_started == false){
                return;
            }
            if (NULL == pFunc)
            {
                return;
            }
            if (args_->type() != TYPEID(ffslot_req_arg))
            {
                return;
            }
            ffslot_req_arg* msg_data = (ffslot_req_arg*)args_;
            try
            {
                if (pFunc == NULL)
                {
                    return;
                }
                WorkerCallMsgt::out_t retmsg;
                try{
                    ffthrift_t::DecodeFromString(retmsg, msg_data->body);
                }
                catch(exception& e_)
                {
                }
                Singleton<FFWorkerPython>::instance().get_ffpython().call_lambda<void>(pFunc, retmsg.body);
            }
            catch(exception& e_)
            {
                LOGERROR((FFWORKER_PYTHON, "ffscene_python_t::call_service exception=%s", e_.what()));
            }
            Py_XDECREF(pFunc);
        }
        virtual FFSlot::FFCallBack* fork() { return new lambda_cb(pFunc); }
        PyObject* pFunc;
    };
    Singleton<FFWorkerPython>::instance().workerRPC(workerindex, cmd, argdata, new lambda_cb(pFuncArg));
}
static void py_syncSharedData(int cmd, const string& data)
{
    Singleton<FFWorkerPython>::instance().getSharedMem().syncSharedData(cmd, data);
}
static bool py_asyncHttp(const string& url_, int timeoutsec, PyObject* pFuncSrc)
{
    struct lambda_cb: public FFSlot::FFCallBack
    {
        lambda_cb(PyObject* pFuncSrc):pFunc(pFuncSrc){}
        virtual void exe(FFSlot::CallBackArg* args_)
        {
            if (NULL == pFunc)
            {
                return;
            }
            if (args_->type() != TYPEID(HttpMgr::http_result_t))
            {
                return;
            }
            HttpMgr::http_result_t* data = (HttpMgr::http_result_t*)args_;

            Singleton<FFWorkerPython>::instance().getRpc().get_tq().produce(TaskBinder::gen(&lambda_cb::call_python, pFunc, data->ret));
        }
        static void call_python(PyObject* pFunc, string retdata)
        {
            try
            {
                if (Singleton<FFWorkerPython>::instance().m_enable_call)
                {
                    Singleton<FFWorkerPython>::instance().get_ffpython().call_lambda<void>(pFunc, retdata);
                }
            }
            catch(exception& e_)
            {
                LOGERROR((FFWORKER_PYTHON, "ffscene_python_t::py_asyncHttp exception<%s>", e_.what()));
            }
            Py_XDECREF(pFunc);
        }
        virtual FFSlot::FFCallBack* fork() { return new lambda_cb(pFunc); }
        PyObject* pFunc;
    };
    
    if (pFuncSrc != NULL)
    {
        Py_INCREF(pFuncSrc);
    }
    
    Singleton<FFWorkerPython>::instance().asyncHttp(url_, timeoutsec, new lambda_cb(pFuncSrc));
    return true;
}
static string py_syncHttp(const string& url_, int timeoutsec)
{
    return Singleton<FFWorkerPython>::instance().syncHttp(url_, timeoutsec);
}
static void when_syncSharedData(int32_t cmd, const string& data){
    try{
        Singleton<FFWorkerPython>::instance().get_ffpython().call<void>(
                    Singleton<FFWorkerPython>::instance().m_ext_name,
                    "when_syncSharedData", cmd, data);
    }
    catch(exception& e_)
    {
        LOGERROR((FFWORKER_PYTHON, "FFWorkerPython::when_syncSharedData exception=%s", e_.what()));
    }
}
static ScriptArgObjPtr toScriptArg(PyObject* pvalue_){
    ScriptArgObjPtr ret = new ScriptArgObj();
    if (PyLong_Check(pvalue_)){
        ret->toInt((long)PyLong_AsLong(pvalue_));
    }
    else if (Py_None == pvalue_){
        return ret;
    }
    else if (Py_False ==  pvalue_){
        ret->toInt(0);
    }
    else if (Py_True ==  pvalue_){
        ret->toInt(1);
    }
    else if (PyInt_Check(pvalue_)){
        ret->toInt((long)PyInt_AsLong(pvalue_));
    }
    else if (PyFloat_Check(pvalue_)){
        ret->toFloat(PyFloat_AsDouble(pvalue_));
    }
    else if (PyString_Check(pvalue_)){
        char* pDest = NULL;
        Py_ssize_t  nLen    = 0;
        PyString_AsStringAndSize(pvalue_, &pDest, &nLen);
        string sval(pDest, nLen);
        ret->toString(sval);
    }
    else if (PyList_Check(pvalue_)){
        ret->toList();
        int n = PyList_Size(pvalue_);
        for (int i = 0; i < n; ++i)
        {
            PyObject *pyElem = PyList_GetItem(pvalue_, i);
            ScriptArgObjPtr elem = toScriptArg(pyElem);
            ret->listVal.push_back(elem);
        }
    }
    else if (PyTuple_Check(pvalue_)){
        ret->toList();
        int n = PyTuple_Size(pvalue_);
        for (int i = 0; i < n; ++i)
        {
            PyObject *pyElem = PyTuple_GetItem(pvalue_, i);
            ScriptArgObjPtr elem = toScriptArg(pyElem);
            ret->listVal.push_back(elem);
        }
    }
    else if (PyDict_Check(pvalue_)){
        ret->toDict();
        PyObject *key = NULL, *value = NULL;
        Py_ssize_t pos = 0;

        string strKey;
        while (PyDict_Next(pvalue_, &pos, &key, &value))
        {
            PyObject *pystr = PyObject_Str(key);
            strKey = PyString_AsString(pystr);
            Py_DECREF(pystr);
            ret->dictVal[strKey] = toScriptArg(value);
        }
    }
    return ret;
}

static PyObject* fromScriptArgToPy(ScriptArgObjPtr pvalue){
    if (!pvalue){
        Py_RETURN_NONE;
    }
    if (pvalue->isNull()){
        Py_RETURN_NONE;
    }
    else if (pvalue->isInt()){
        return PyLong_FromLong(pvalue->getInt());
    }
    else if (pvalue->isFloat()){
        return PyFloat_FromDouble(pvalue->getFloat());
    }
    else if (pvalue->isString()){
        return PyString_FromStringAndSize(pvalue->getString().c_str(), pvalue->getString().size());
    }
    else if (pvalue->isList()){
        PyObject* ret = PyList_New(pvalue->listVal.size());
        for (size_t i = 0; i < pvalue->listVal.size(); ++i){
            PyList_SetItem(ret, i, fromScriptArgToPy(pvalue->listVal[i]));
        }
        return ret;
    }
    else if (pvalue->isDict()){
        PyObject* ret = PyDict_New();
        map<string, SharedPtr<ScriptArgObj> >::iterator it = pvalue->dictVal.begin();
        for (; it != pvalue->dictVal.end(); ++it)
        {
            PyObject *k = PyString_FromStringAndSize(it->first.c_str(), it->first.size());
            PyObject *v = fromScriptArgToPy(it->second);
            PyDict_SetItem(ret, k, v);
            Py_DECREF(k);
            Py_DECREF(v);
        }
        return ret;
    }
    Py_RETURN_NONE;
}
static PyObject* callFunc(PyObject* pvalue){
    LOGINFO((FFWORKER_PYTHON, "FFWorkerPython::callFunc begin 1"));
    if (!pvalue){
        Py_RETURN_NONE;
    }
    if (false == PyTuple_Check(pvalue)){
        LOGINFO((FFWORKER_PYTHON, "FFWorkerPython::callFunc begin notlist"));
        Py_RETURN_NONE;
    }
    ScriptArgs scriptArgs;
    int n = PyTuple_Size(pvalue);
    if (n <= 0){
        LOGERROR((FFWORKER_PYTHON, "FFWorkerPython::callFunc no funcname"));
        Py_RETURN_NONE;
    }
    PyObject *pyName = PyTuple_GetItem(pvalue, 0);
    if (false == PyString_Check(pyName)){
        LOGERROR((FFWORKER_PYTHON, "FFWorkerPython::callFunc no funcname, type error"));
        Py_RETURN_NONE;
    }
    char* pDest = NULL;
    Py_ssize_t  nLen    = 0;
    PyString_AsStringAndSize(pyName, &pDest, &nLen);
    string funcName(pDest, nLen);
    
    for (int i = 1; i < n; ++i)
    {
        PyObject *pyElem = PyTuple_GetItem(pvalue, i);
        ScriptArgObjPtr elem = toScriptArg(pyElem);
        scriptArgs.args.push_back(elem);
    }
    
    LOGTRACE((FFWORKER_PYTHON, "FFWorkerPython::callFunc begin argsize=%d", scriptArgs.args.size()));
    if (false == SCRIPT_UTIL.call(funcName, scriptArgs)){
        LOGERROR((FFWORKER_PYTHON, "FFWorkerPython::callFunc no funcname:%s", funcName));
        Py_RETURN_NONE;
    }
    PyObject* ret = fromScriptArgToPy(scriptArgs.getReturnValue());
    return ret;
}
int FFWorkerPython::py_init(const string& py_root)
{
    string path;
    std::size_t pos = py_root.find_last_of("/");
    if (pos != string::npos)
    {
        path = py_root.substr(0, pos+1);
        m_ext_name = py_root.substr(pos+1, py_root.size() - pos - 1);
        ffpython_t::add_path(path);
    }
    else{
        m_ext_name = py_root;
        ffpython_t::add_path("./");
    }
    pos = m_ext_name.find(".py");
    m_ext_name = m_ext_name.substr(0, pos);

    LOGTRACE((FFWORKER_PYTHON, "FFWorkerPython::py_init begin path:%s, m_ext_name:%s", path, m_ext_name));
    
    getSharedMem().setNotifyFunc(when_syncSharedData);
    
    (*m_ffpython).reg(&FFDb::escape, "escape")
                 .reg(&py_send_msg_session, "sessionSendMsg")
                 .reg(&py_broadcast_msg_gate, "gateBroadcastMsg")
                 .reg(&py_multicast_msg_session, "sessionMulticastMsg")
                 .reg(&py_closeSession, "sessionClose")
                 .reg(&py_change_session_worker, "sessionChangeWorker")
                 .reg(&py_getSessionGate, "getSessionGate")
                 .reg(&py_getSessionIp, "getSessionIp")
                 .reg(&py_isExist, "isExist")
                 .reg(&py_reload, "reload")
                 .reg(&py_log, "log")
                 .reg(&py_regTimer, "regTimer")
                 .reg(&py_connectDB, "connectDB")
                 .reg(&py_asyncQuery, "asyncQuery")
                 .reg(&py_query, "query")
                 .reg(&py_asyncQueryGroupMod, "asyncQueryGroupMod")
                 .reg(&py_queryGroupMod, "queryGroupMod")
                 .reg(&py_workerRPC, "workerRPC")
                 .reg(&py_syncSharedData, "syncSharedData")
                 .reg(&py_asyncHttp, "asyncHttp")
                 .reg(&py_syncHttp, "syncHttp")
                 .reg(&py_writeLockGuard, "writeLockGuard")
                 .reg(&callFunc, "callFunc", "", true)
                 ;
    
            
    (*m_ffpython).init(EXT_NAME);

    DB_MGR_OBJ.start();
    
    int ret = -2;
    
    try{
        
        Mutex                    mutex;
        ConditionVar            cond(mutex);
        
        LockGuard lock(mutex);
        getRpc().get_tq().produce(TaskBinder::gen(&FFWorkerPython::process_init, this, &cond, &ret));
        LOGINFO((FFWORKER_PYTHON, "FFWorkerPython::begin init py"));
        do {
            LOGINFO((FFWORKER_PYTHON, "FFWorkerPython::wait init"));
            cond.time_wait(100);
        }while (ret == -2);
        LOGINFO((FFWORKER_PYTHON, "FFWorkerPython::process_init return"));
        if (ret < 0)
        {
            this->close();
            return -1;
        }
    }
    catch(exception& e_)
    {
        return -1;
    }
    m_started = true;
    LOGTRACE((FFWORKER_PYTHON, "FFWorkerPython::py_init end ok"));
    return ret;
}
//!!处理初始化逻辑
int FFWorkerPython::process_init(ConditionVar* var, int* ret)
{
    try{
        (*m_ffpython).load(m_ext_name);
        *ret = 0;
    }
    catch(exception& e_)
    {
        *ret = -1;
        LOGERROR((FFWORKER_PYTHON, "FFWorkerPython::open failed er=<%s>", e_.what()));
    }
    var->signal();
    LOGINFO((FFWORKER_PYTHON, "FFWorkerPython::process_init end"));
    return 0;
}
void FFWorkerPython::py_cleanup()
{
    try
    {
        (*m_ffpython).call<void>(m_ext_name, string("cleanup"));
    }
    catch(exception& e_)
    {
        LOGERROR((FFWORKER_PYTHON, "py_cleanup failed er=<%s>", e_.what()));
    }
    m_enable_call = false;
    DB_MGR_OBJ.stop();
    LOGINFO((FFWORKER_PYTHON, "FFWorkerPython::py_cleanup end"));
}
int FFWorkerPython::close()
{
    getRpc().get_tq().produce(TaskBinder::gen(&FFWorkerPython::py_cleanup, this));
    FFWorker::close();
    if (false == m_started)
        return 0;
    m_started = false;

    LOGINFO((FFWORKER_PYTHON, "FFWorkerPython::close end"));
    return 0;
}

string FFWorkerPython::reload(const string& name_)
{
    AUTO_PERF();
    LOGTRACE((FFWORKER_PYTHON, "FFWorkerPython::reload begin name_[%s]", name_));
    try
    {
        ffpython_t::reload(name_);
    }
    catch(exception& e_)
    {
        LOGERROR((FFWORKER_PYTHON, "FFWorkerPython::reload exeception=%s", e_.what()));
        return e_.what();
    }
    LOGTRACE((FFWORKER_PYTHON, "FFWorkerPython::reload end ok name_[%s]", name_));
    return "";
}
void FFWorkerPython::pylog(int level_, const string& mod_, const string& content_)
{
    switch (level_)
    {
        case 1:
        {
            LOGFATAL((mod_.c_str(), "%s", content_));
        }
        break;
        case 2:
        {
            LOGERROR((mod_.c_str(), "%s", content_));
        }
        break;
        case 3:
        {
            LOGWARN((mod_.c_str(), "%s", content_));
        }
        break;
        case 4:
        {
            LOGINFO((mod_.c_str(), "%s", content_));
        }
        break;
        case 5:
        {
            LOGDEBUG((mod_.c_str(), "%s", content_));
        }
        break;
        case 6:
        {
            LOGTRACE((mod_.c_str(), "%s", content_));
        }
        break;
        default:
        {
            LOGTRACE((mod_.c_str(), "%s", content_));
        }
        break;
    }
}

int FFWorkerPython::onSessionReq(userid_t session_id, uint16_t cmd, const std::string& data)
{
    LOGTRACE((FFWORKER_PYTHON, "onSessionReq session_id=%d,cmd=<%d>", session_id, cmd));
    try
    {
        (*m_ffpython).call<void>(m_ext_name, "onSessionReq", session_id, cmd, data);//
    }
    catch(exception& e_)
    {
        LOGERROR((FFWORKER_PYTHON, "onSessionReq failed er=<%s>", e_.what()));
    }
    return 0;
}

int FFWorkerPython::onSessionOffline(userid_t session_id)
{
    try
    {
        (*m_ffpython).call<void>(m_ext_name, "onSessionOffline", session_id);
    }
    catch(exception& e_)
    {
        LOGERROR((FFWORKER_PYTHON, "onSessionOffline failed er=<%s>", e_.what()));
    }
    return 0;
}
int FFWorkerPython::FFWorkerPython::onSessionEnter(userid_t session_id, const std::string& extra_data)
{
    try
    {
        (*m_ffpython).call<void>(m_ext_name, "onSessionEnter", session_id, extra_data);
    }
    catch(exception& e_)
    {
        LOGERROR((FFWORKER_PYTHON, "onSessionEnter failed er=<%s>", e_.what()));
    }
    return 0;
}

string FFWorkerPython::onWorkerCall(uint16_t cmd, const std::string& body)
{
    string ret;
    try
    {
        ret = (*m_ffpython).call<string>(m_ext_name, "onWorkerCall", cmd, body);
    }
    catch(exception& e_)
    {
        ret = "!";
        ret += e_.what();
        LOGERROR((FFWORKER_PYTHON, "onWorkerCall failed er=<%s>", ret));
        
    }
    return ret;
}
