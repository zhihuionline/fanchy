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


#if !SILVERLIGHT
[Serializable]
#endif
public partial class GateRouteMsgToSessionReq : TBase
{
  private List<long> _sessionId;
  private short _cmd;
  private byte[] _body;

  public List<long> SessionId
  {
    get
    {
      return _sessionId;
    }
    set
    {
      __isset.sessionId = true;
      this._sessionId = value;
    }
  }

  public short Cmd
  {
    get
    {
      return _cmd;
    }
    set
    {
      __isset.cmd = true;
      this._cmd = value;
    }
  }

  public byte[] Body
  {
    get
    {
      return _body;
    }
    set
    {
      __isset.body = true;
      this._body = value;
    }
  }


  public Isset __isset;
  #if !SILVERLIGHT
  [Serializable]
  #endif
  public struct Isset {
    public bool sessionId;
    public bool cmd;
    public bool body;
  }

  public GateRouteMsgToSessionReq() {
    this._sessionId = new List<long>();
    this.__isset.sessionId = true;
    this._cmd = 0;
    this.__isset.cmd = true;
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
          if (field.Type == TType.List) {
            {
              SessionId = new List<long>();
              TList _list0 = iprot.ReadListBegin();
              for( int _i1 = 0; _i1 < _list0.Count; ++_i1)
              {
                long _elem2 = 0;
                _elem2 = iprot.ReadI64();
                SessionId.Add(_elem2);
              }
              iprot.ReadListEnd();
            }
          } else { 
            TProtocolUtil.Skip(iprot, field.Type);
          }
          break;
        case 2:
          if (field.Type == TType.I16) {
            Cmd = iprot.ReadI16();
          } else { 
            TProtocolUtil.Skip(iprot, field.Type);
          }
          break;
        case 3:
          if (field.Type == TType.String) {
            Body = iprot.ReadBinary();
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
    TStruct struc = new TStruct("GateRouteMsgToSessionReq");
    oprot.WriteStructBegin(struc);
    TField field = new TField();
    if (SessionId != null && __isset.sessionId) {
      field.Name = "sessionId";
      field.Type = TType.List;
      field.ID = 1;
      oprot.WriteFieldBegin(field);
      {
        oprot.WriteListBegin(new TList(TType.I64, SessionId.Count));
        foreach (long _iter3 in SessionId)
        {
          oprot.WriteI64(_iter3);
        }
        oprot.WriteListEnd();
      }
      oprot.WriteFieldEnd();
    }
    if (__isset.cmd) {
      field.Name = "cmd";
      field.Type = TType.I16;
      field.ID = 2;
      oprot.WriteFieldBegin(field);
      oprot.WriteI16(Cmd);
      oprot.WriteFieldEnd();
    }
    if (Body != null && __isset.body) {
      field.Name = "body";
      field.Type = TType.String;
      field.ID = 3;
      oprot.WriteFieldBegin(field);
      oprot.WriteBinary(Body);
      oprot.WriteFieldEnd();
    }
    oprot.WriteFieldStop();
    oprot.WriteStructEnd();
  }

  public override string ToString() {
    StringBuilder sb = new StringBuilder("GateRouteMsgToSessionReq(");
    sb.Append("SessionId: ");
    sb.Append(SessionId);
    sb.Append(",Cmd: ");
    sb.Append(Cmd);
    sb.Append(",Body: ");
    sb.Append(Body);
    sb.Append(")");
    return sb.ToString();
  }

}

