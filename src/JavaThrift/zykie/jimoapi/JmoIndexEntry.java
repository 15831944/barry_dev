/**
 * Autogenerated by Thrift Compiler (0.9.1)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
package zykie.jimoapi;

import org.apache.thrift.scheme.IScheme;
import org.apache.thrift.scheme.SchemeFactory;
import org.apache.thrift.scheme.StandardScheme;

import org.apache.thrift.scheme.TupleScheme;
import org.apache.thrift.protocol.TTupleProtocol;
import org.apache.thrift.protocol.TProtocolException;
import org.apache.thrift.EncodingUtils;
import org.apache.thrift.TException;
import org.apache.thrift.async.AsyncMethodCallback;
import org.apache.thrift.server.AbstractNonblockingServer.*;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.EnumMap;
import java.util.Set;
import java.util.HashSet;
import java.util.EnumSet;
import java.util.Collections;
import java.util.BitSet;
import java.nio.ByteBuffer;
import java.util.Arrays;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class JmoIndexEntry implements org.apache.thrift.TBase<JmoIndexEntry, JmoIndexEntry._Fields>, java.io.Serializable, Cloneable, Comparable<JmoIndexEntry> {
  private static final org.apache.thrift.protocol.TStruct STRUCT_DESC = new org.apache.thrift.protocol.TStruct("JmoIndexEntry");

  private static final org.apache.thrift.protocol.TField KEY_FIELD_DESC = new org.apache.thrift.protocol.TField("key", org.apache.thrift.protocol.TType.STRING, (short)1);
  private static final org.apache.thrift.protocol.TField DOCID_FIELD_DESC = new org.apache.thrift.protocol.TField("docid", org.apache.thrift.protocol.TType.I64, (short)2);

  private static final Map<Class<? extends IScheme>, SchemeFactory> schemes = new HashMap<Class<? extends IScheme>, SchemeFactory>();
  static {
    schemes.put(StandardScheme.class, new JmoIndexEntryStandardSchemeFactory());
    schemes.put(TupleScheme.class, new JmoIndexEntryTupleSchemeFactory());
  }

  public String key; // required
  public long docid; // required

  /** The set of fields this struct contains, along with convenience methods for finding and manipulating them. */
  public enum _Fields implements org.apache.thrift.TFieldIdEnum {
    KEY((short)1, "key"),
    DOCID((short)2, "docid");

    private static final Map<String, _Fields> byName = new HashMap<String, _Fields>();

    static {
      for (_Fields field : EnumSet.allOf(_Fields.class)) {
        byName.put(field.getFieldName(), field);
      }
    }

    /**
     * Find the _Fields constant that matches fieldId, or null if its not found.
     */
    public static _Fields findByThriftId(int fieldId) {
      switch(fieldId) {
        case 1: // KEY
          return KEY;
        case 2: // DOCID
          return DOCID;
        default:
          return null;
      }
    }

    /**
     * Find the _Fields constant that matches fieldId, throwing an exception
     * if it is not found.
     */
    public static _Fields findByThriftIdOrThrow(int fieldId) {
      _Fields fields = findByThriftId(fieldId);
      if (fields == null) throw new IllegalArgumentException("Field " + fieldId + " doesn't exist!");
      return fields;
    }

    /**
     * Find the _Fields constant that matches name, or null if its not found.
     */
    public static _Fields findByName(String name) {
      return byName.get(name);
    }

    private final short _thriftId;
    private final String _fieldName;

    _Fields(short thriftId, String fieldName) {
      _thriftId = thriftId;
      _fieldName = fieldName;
    }

    public short getThriftFieldId() {
      return _thriftId;
    }

    public String getFieldName() {
      return _fieldName;
    }
  }

  // isset id assignments
  private static final int __DOCID_ISSET_ID = 0;
  private byte __isset_bitfield = 0;
  public static final Map<_Fields, org.apache.thrift.meta_data.FieldMetaData> metaDataMap;
  static {
    Map<_Fields, org.apache.thrift.meta_data.FieldMetaData> tmpMap = new EnumMap<_Fields, org.apache.thrift.meta_data.FieldMetaData>(_Fields.class);
    tmpMap.put(_Fields.KEY, new org.apache.thrift.meta_data.FieldMetaData("key", org.apache.thrift.TFieldRequirementType.DEFAULT, 
        new org.apache.thrift.meta_data.FieldValueMetaData(org.apache.thrift.protocol.TType.STRING)));
    tmpMap.put(_Fields.DOCID, new org.apache.thrift.meta_data.FieldMetaData("docid", org.apache.thrift.TFieldRequirementType.DEFAULT, 
        new org.apache.thrift.meta_data.FieldValueMetaData(org.apache.thrift.protocol.TType.I64)));
    metaDataMap = Collections.unmodifiableMap(tmpMap);
    org.apache.thrift.meta_data.FieldMetaData.addStructMetaDataMap(JmoIndexEntry.class, metaDataMap);
  }

  public JmoIndexEntry() {
  }

  public JmoIndexEntry(
    String key,
    long docid)
  {
    this();
    this.key = key;
    this.docid = docid;
    setDocidIsSet(true);
  }

  /**
   * Performs a deep copy on <i>other</i>.
   */
  public JmoIndexEntry(JmoIndexEntry other) {
    __isset_bitfield = other.__isset_bitfield;
    if (other.isSetKey()) {
      this.key = other.key;
    }
    this.docid = other.docid;
  }

  public JmoIndexEntry deepCopy() {
    return new JmoIndexEntry(this);
  }

  @Override
  public void clear() {
    this.key = null;
    setDocidIsSet(false);
    this.docid = 0;
  }

  public String getKey() {
    return this.key;
  }

  public JmoIndexEntry setKey(String key) {
    this.key = key;
    return this;
  }

  public void unsetKey() {
    this.key = null;
  }

  /** Returns true if field key is set (has been assigned a value) and false otherwise */
  public boolean isSetKey() {
    return this.key != null;
  }

  public void setKeyIsSet(boolean value) {
    if (!value) {
      this.key = null;
    }
  }

  public long getDocid() {
    return this.docid;
  }

  public JmoIndexEntry setDocid(long docid) {
    this.docid = docid;
    setDocidIsSet(true);
    return this;
  }

  public void unsetDocid() {
    __isset_bitfield = EncodingUtils.clearBit(__isset_bitfield, __DOCID_ISSET_ID);
  }

  /** Returns true if field docid is set (has been assigned a value) and false otherwise */
  public boolean isSetDocid() {
    return EncodingUtils.testBit(__isset_bitfield, __DOCID_ISSET_ID);
  }

  public void setDocidIsSet(boolean value) {
    __isset_bitfield = EncodingUtils.setBit(__isset_bitfield, __DOCID_ISSET_ID, value);
  }

  public void setFieldValue(_Fields field, Object value) {
    switch (field) {
    case KEY:
      if (value == null) {
        unsetKey();
      } else {
        setKey((String)value);
      }
      break;

    case DOCID:
      if (value == null) {
        unsetDocid();
      } else {
        setDocid((Long)value);
      }
      break;

    }
  }

  public Object getFieldValue(_Fields field) {
    switch (field) {
    case KEY:
      return getKey();

    case DOCID:
      return Long.valueOf(getDocid());

    }
    throw new IllegalStateException();
  }

  /** Returns true if field corresponding to fieldID is set (has been assigned a value) and false otherwise */
  public boolean isSet(_Fields field) {
    if (field == null) {
      throw new IllegalArgumentException();
    }

    switch (field) {
    case KEY:
      return isSetKey();
    case DOCID:
      return isSetDocid();
    }
    throw new IllegalStateException();
  }

  @Override
  public boolean equals(Object that) {
    if (that == null)
      return false;
    if (that instanceof JmoIndexEntry)
      return this.equals((JmoIndexEntry)that);
    return false;
  }

  public boolean equals(JmoIndexEntry that) {
    if (that == null)
      return false;

    boolean this_present_key = true && this.isSetKey();
    boolean that_present_key = true && that.isSetKey();
    if (this_present_key || that_present_key) {
      if (!(this_present_key && that_present_key))
        return false;
      if (!this.key.equals(that.key))
        return false;
    }

    boolean this_present_docid = true;
    boolean that_present_docid = true;
    if (this_present_docid || that_present_docid) {
      if (!(this_present_docid && that_present_docid))
        return false;
      if (this.docid != that.docid)
        return false;
    }

    return true;
  }

  @Override
  public int hashCode() {
    return 0;
  }

  @Override
  public int compareTo(JmoIndexEntry other) {
    if (!getClass().equals(other.getClass())) {
      return getClass().getName().compareTo(other.getClass().getName());
    }

    int lastComparison = 0;

    lastComparison = Boolean.valueOf(isSetKey()).compareTo(other.isSetKey());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetKey()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.key, other.key);
      if (lastComparison != 0) {
        return lastComparison;
      }
    }
    lastComparison = Boolean.valueOf(isSetDocid()).compareTo(other.isSetDocid());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetDocid()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.docid, other.docid);
      if (lastComparison != 0) {
        return lastComparison;
      }
    }
    return 0;
  }

  public _Fields fieldForId(int fieldId) {
    return _Fields.findByThriftId(fieldId);
  }

  public void read(org.apache.thrift.protocol.TProtocol iprot) throws org.apache.thrift.TException {
    schemes.get(iprot.getScheme()).getScheme().read(iprot, this);
  }

  public void write(org.apache.thrift.protocol.TProtocol oprot) throws org.apache.thrift.TException {
    schemes.get(oprot.getScheme()).getScheme().write(oprot, this);
  }

  @Override
  public String toString() {
    StringBuilder sb = new StringBuilder("JmoIndexEntry(");
    boolean first = true;

    sb.append("key:");
    if (this.key == null) {
      sb.append("null");
    } else {
      sb.append(this.key);
    }
    first = false;
    if (!first) sb.append(", ");
    sb.append("docid:");
    sb.append(this.docid);
    first = false;
    sb.append(")");
    return sb.toString();
  }

  public void validate() throws org.apache.thrift.TException {
    // check for required fields
    // check for sub-struct validity
  }

  private void writeObject(java.io.ObjectOutputStream out) throws java.io.IOException {
    try {
      write(new org.apache.thrift.protocol.TCompactProtocol(new org.apache.thrift.transport.TIOStreamTransport(out)));
    } catch (org.apache.thrift.TException te) {
      throw new java.io.IOException(te);
    }
  }

  private void readObject(java.io.ObjectInputStream in) throws java.io.IOException, ClassNotFoundException {
    try {
      // it doesn't seem like you should have to do this, but java serialization is wacky, and doesn't call the default constructor.
      __isset_bitfield = 0;
      read(new org.apache.thrift.protocol.TCompactProtocol(new org.apache.thrift.transport.TIOStreamTransport(in)));
    } catch (org.apache.thrift.TException te) {
      throw new java.io.IOException(te);
    }
  }

  private static class JmoIndexEntryStandardSchemeFactory implements SchemeFactory {
    public JmoIndexEntryStandardScheme getScheme() {
      return new JmoIndexEntryStandardScheme();
    }
  }

  private static class JmoIndexEntryStandardScheme extends StandardScheme<JmoIndexEntry> {

    public void read(org.apache.thrift.protocol.TProtocol iprot, JmoIndexEntry struct) throws org.apache.thrift.TException {
      org.apache.thrift.protocol.TField schemeField;
      iprot.readStructBegin();
      while (true)
      {
        schemeField = iprot.readFieldBegin();
        if (schemeField.type == org.apache.thrift.protocol.TType.STOP) { 
          break;
        }
        switch (schemeField.id) {
          case 1: // KEY
            if (schemeField.type == org.apache.thrift.protocol.TType.STRING) {
              struct.key = iprot.readString();
              struct.setKeyIsSet(true);
            } else { 
              org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
            }
            break;
          case 2: // DOCID
            if (schemeField.type == org.apache.thrift.protocol.TType.I64) {
              struct.docid = iprot.readI64();
              struct.setDocidIsSet(true);
            } else { 
              org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
            }
            break;
          default:
            org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
        }
        iprot.readFieldEnd();
      }
      iprot.readStructEnd();

      // check for required fields of primitive type, which can't be checked in the validate method
      struct.validate();
    }

    public void write(org.apache.thrift.protocol.TProtocol oprot, JmoIndexEntry struct) throws org.apache.thrift.TException {
      struct.validate();

      oprot.writeStructBegin(STRUCT_DESC);
      if (struct.key != null) {
        oprot.writeFieldBegin(KEY_FIELD_DESC);
        oprot.writeString(struct.key);
        oprot.writeFieldEnd();
      }
      oprot.writeFieldBegin(DOCID_FIELD_DESC);
      oprot.writeI64(struct.docid);
      oprot.writeFieldEnd();
      oprot.writeFieldStop();
      oprot.writeStructEnd();
    }

  }

  private static class JmoIndexEntryTupleSchemeFactory implements SchemeFactory {
    public JmoIndexEntryTupleScheme getScheme() {
      return new JmoIndexEntryTupleScheme();
    }
  }

  private static class JmoIndexEntryTupleScheme extends TupleScheme<JmoIndexEntry> {

    @Override
    public void write(org.apache.thrift.protocol.TProtocol prot, JmoIndexEntry struct) throws org.apache.thrift.TException {
      TTupleProtocol oprot = (TTupleProtocol) prot;
      BitSet optionals = new BitSet();
      if (struct.isSetKey()) {
        optionals.set(0);
      }
      if (struct.isSetDocid()) {
        optionals.set(1);
      }
      oprot.writeBitSet(optionals, 2);
      if (struct.isSetKey()) {
        oprot.writeString(struct.key);
      }
      if (struct.isSetDocid()) {
        oprot.writeI64(struct.docid);
      }
    }

    @Override
    public void read(org.apache.thrift.protocol.TProtocol prot, JmoIndexEntry struct) throws org.apache.thrift.TException {
      TTupleProtocol iprot = (TTupleProtocol) prot;
      BitSet incoming = iprot.readBitSet(2);
      if (incoming.get(0)) {
        struct.key = iprot.readString();
        struct.setKeyIsSet(true);
      }
      if (incoming.get(1)) {
        struct.docid = iprot.readI64();
        struct.setDocidIsSet(true);
      }
    }
  }

}

