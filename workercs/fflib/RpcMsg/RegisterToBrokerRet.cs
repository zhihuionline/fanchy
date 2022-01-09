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
public partial class RegisterToBrokerRet : TBase
{
  private short _registerFlag;
  private long _nodeId;
  private Dictionary<string, long> _service2nodeId;

  public short RegisterFlag
  {
    get
    {
      return _registerFlag;
    }
    set
    {
      __isset.registerFlag = true;
      this._registerFlag = value;
    }
  }

  public long NodeId
  {
    get
    {
      return _nodeId;
    }
    set
    {
      __isset.nodeId = true;
      this._nodeId = value;
    }
  }

  public Dictionary<string, long> Service2nodeId
  {
    get
    {
      return _service2nodeId;
    }
    set
    {
      __isset.service2nodeId = true;
      this._service2nodeId = value;
    }
  }


  public Isset __isset;
  #if !SILVERLIGHT
  [Serializable]
  #endif
  public struct Isset {
    public bool registerFlag;
    public bool nodeId;
    public bool service2nodeId;
  }

  public RegisterToBrokerRet() {
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
          if (field.Type == TType.I16) {
            RegisterFlag = iprot.ReadI16();
          } else { 
            TProtocolUtil.Skip(iprot, field.Type);
          }
          break;
        case 2:
          if (field.Type == TType.I64) {
            NodeId = iprot.ReadI64();
          } else { 
            TProtocolUtil.Skip(iprot, field.Type);
          }
          break;
        case 3:
          if (field.Type == TType.Map) {
            {
              Service2nodeId = new Dictionary<string, long>();
              TMap _map4 = iprot.ReadMapBegin();
              for( int _i5 = 0; _i5 < _map4.Count; ++_i5)
              {
                string _key6;
                long _val7;
                _key6 = iprot.ReadString();
                _val7 = iprot.ReadI64();
                Service2nodeId[_key6] = _val7;
              }
              iprot.ReadMapEnd();
            }
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
    TStruct struc = new TStruct("RegisterToBrokerRet");
    oprot.WriteStructBegin(struc);
    TField field = new TField();
    if (__isset.registerFlag) {
      field.Name = "registerFlag";
      field.Type = TType.I16;
      field.ID = 1;
      oprot.WriteFieldBegin(field);
      oprot.WriteI16(RegisterFlag);
      oprot.WriteFieldEnd();
    }
    if (__isset.nodeId) {
      field.Name = "nodeId";
      field.Type = TType.I64;
      field.ID = 2;
      oprot.WriteFieldBegin(field);
      oprot.WriteI64(NodeId);
      oprot.WriteFieldEnd();
    }
    if (Service2nodeId != null && __isset.service2nodeId) {
      field.Name = "service2nodeId";
      field.Type = TType.Map;
      field.ID = 3;
      oprot.WriteFieldBegin(field);
      {
        oprot.WriteMapBegin(new TMap(TType.String, TType.I64, Service2nodeId.Count));
        foreach (string _iter8 in Service2nodeId.Keys)
        {
          oprot.WriteString(_iter8);
          oprot.WriteI64(Service2nodeId[_iter8]);
        }
        oprot.WriteMapEnd();
      }
      oprot.WriteFieldEnd();
    }
    oprot.WriteFieldStop();
    oprot.WriteStructEnd();
  }

  public override string ToString() {
    StringBuilder sb = new StringBuilder("RegisterToBrokerRet(");
    sb.Append("RegisterFlag: ");
    sb.Append(RegisterFlag);
    sb.Append(",NodeId: ");
    sb.Append(NodeId);
    sb.Append(",Service2nodeId: ");
    sb.Append(Service2nodeId);
    sb.Append(")");
    return sb.ToString();
  }

}

