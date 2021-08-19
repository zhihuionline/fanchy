/**
 * Autogenerated by Thrift Compiler (0.9.1)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.IO;
using Thrift;
using Thrift.Collections;
using System.Runtime.Serialization;
using Thrift.Protocol;
using Thrift.Transport;

namespace ff
{

  #if !SILVERLIGHT
  [Serializable]
  #endif
  public partial class GateCloseSessionReq : TBase
  {
    private long _session_id;

    public long Session_id
    {
      get
      {
        return _session_id;
      }
      set
      {
        __isset.session_id = true;
        this._session_id = value;
      }
    }


    public Isset __isset;
    #if !SILVERLIGHT
    [Serializable]
    #endif
    public struct Isset {
      public bool session_id;
    }

    public GateCloseSessionReq() {
      this._session_id = 0;
      this.__isset.session_id = true;
    }

    public void Read (TProtocol iprot)
    {
      TField field;
      iprot.ReadStructBegin();
      while (true)
      {
        field = iprot.ReadFieldBegin();
        if (field.Type == TType.Stop) { 
          break;
        }
        switch (field.ID)
        {
          case 1:
            if (field.Type == TType.I64) {
              Session_id = iprot.ReadI64();
            } else { 
              TProtocolUtil.Skip(iprot, field.Type);
            }
            break;
          default: 
            TProtocolUtil.Skip(iprot, field.Type);
            break;
        }
        iprot.ReadFieldEnd();
      }
      iprot.ReadStructEnd();
    }

    public void Write(TProtocol oprot) {
      TStruct struc = new TStruct("GateCloseSessionReq");
      oprot.WriteStructBegin(struc);
      TField field = new TField();
      if (__isset.session_id) {
        field.Name = "session_id";
        field.Type = TType.I64;
        field.ID = 1;
        oprot.WriteFieldBegin(field);
        oprot.WriteI64(Session_id);
        oprot.WriteFieldEnd();
      }
      oprot.WriteFieldStop();
      oprot.WriteStructEnd();
    }

    public override string ToString() {
      StringBuilder sb = new StringBuilder("GateCloseSessionReq(");
      sb.Append("Session_id: ");
      sb.Append(Session_id);
      sb.Append(")");
      return sb.ToString();
    }

  }

}
