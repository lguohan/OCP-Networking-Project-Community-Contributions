SAI Hash Proposal
=====================

 Title       | SAI Hash Proposal
-------------|----------------------
 Authors     | Microsoft
 Status      | In review
 Type        | Standards track
 Created     | 04/20/2015
 SAI-Version | 0.9.3

---------

## Overview ##

SAI hash object is used to equally distribute different packets to target objects, e.g., the sai next hops. Hash is used to implement ECMP and LAG.

In the abstraction of SAI, every switch has a few global hash objects to handle different types of packets. The hash attributes of saiswitch are used to specify those hash objects. Saiswitch has two groups of hash attributes, an ECMP group and a LAG group.

For the ECMP group, it has  the following attributes:

* SAI\_ECMP\_HASH specifies the hash object to handle all the packets going through ECMP.
* SAI\_ECMP\_IPV4\_HASH specifies the hash object to handle all the IPv4 packets going through ECMP.
* SAI\_ECMP\_IPV4\_IN\_IPV4\_HASH specifies the hash object to handle all the IPv4-In-IPv4 packets going through ECMP.

For the LAG group, it has  the following attributes:

* SAI\_LAG\_HASH specifies the hash object to handle all the packets going through LAG.
* SAI\_LAG\_IPV4\_HASH specifies the hash object to handle all the IPv4 packets going through LAG.
* SAI\_LAG\_IPV4\_IN\_IPV4\_HASH specifies the hash object to handle all the IPv4-In-IPv4 packets going through LAG.

Default hash objects for these attributes should be created when the switch is initialized. Users could override them with their own hash object later.

Sai hash object is comprised of three parts, hash seed, hash fields, hash algorithm. Sai hash object takes two steps to achieve its goal:

1. Extract certain fields from the packet.
2. Compute the hash value based on the hash algorithm.

There are two ways to extract the fields from the packet. The first one is to used the pre-defined fields, e.g., the source IP address for a IP packet, or the source port of a TCP packet. The second one is to use UDF (User Defined Field), which provides users the flexibility to extract customized fields from packets. SAI allows users to use both ways simultaneously. Hash algortihm is pre-defined. Currently, SAI supports the CRC based algorithm, the XOR based algorithm, and the random based algortihm.


## Specification ##

### Changes To sai.h ###

A new type **SAI_API_HASH** is added.

~~~cpp
/*
*
* Defined API sets have assigned ID's. If specific api method table changes
* in any way (method signature, number of methods), a new ID needs to be
* created (e.g. VLAN2) and old API still may need to be supported for
* compatibility with older adapter hosts.
*
*/
typedef enum _sai_api_t
{
    SAI_API_UNSPECIFIED      =  0,
    SAI_API_SWITCH           =  1,  /* sai_switch_api_t */
    SAI_API_PORT             =  2,  /* sai_port_api_t */
    SAI_API_FDB              =  3,  /* sai_fdb_api_t */
    SAI_API_VLAN             =  4,  /* sai_vlan_api_t */
    SAI_API_VIRTUAL_ROUTER   =  5,  /* sai_virtual_router_api_t */
    SAI_API_ROUTE            =  6,  /* sai_route_api_t */
    SAI_API_NEXT_HOP         =  7,  /* sai_next_hop_api_t */
    SAI_API_NEXT_HOP_GROUP   =  8,  /* sai_next_hop_group_api_t */
    SAI_API_ROUTER_INTERFACE =  9,  /* sai_router_interface_api_t */
    SAI_API_NEIGHBOR         = 10,  /* sai_neighbor_api_t */
    SAI_API_QOS              = 11,  /* sai_qos_api_t */
    SAI_API_ACL              = 12,  /* sai_acl_api_t */
    SAI_API_HOST_INTERFACE   = 13,  /* sai_host_interface_api_t */
    SAI_API_MIRROR           = 14,  /* sai_mirror_api_t */
    SAI_API_SAMPLEPACKET     = 15,  /* sai_samplepacket_api_t */
    SAI_API_STP              = 16,  /* sai_stp_api_t */
    SAI_API_LAG              = 17,  /* sai_lag_api_t */
    SAI_API_HASH             = 18,  /* sai_hash_api_t */
} sai_api_t;
~~~

### Changes To saiswitch.h ###

Existing types, **sai_switch_ecmp_hash_type_t** and **sai_switch_ecmp_hash_fields_t**, are deleted.

A few hash related attributes are added into sai\_switch\_attr\_t.

~~~cpp
/*
*  Attribute Id in sai_set_switch_attribute() and 
*  sai_get_switch_attribute() calls
*/
typedef enum _sai_switch_attr_t
{
    /* READ-ONLY */

    /* The number of ports on the switch [uint32_t] */
    SAI_SWITCH_ATTR_PORT_NUMBER,

    ...

    /* Sai default hash algorithm [sai_hash_algorithm] (default to SAI_HASH_ALGORITHM_CRC) */
    SAI_DEFAULT_HASH_ALGORITHM,

    /* Sai default hash seed [uint32_t] (default to 0) */
    SAI_DEFAULT_HASH_SEED,

    /* The hash object for packets going throught ECMP [sai_object_id_t] */
    SAI_ECMP_HASH,

    /* The hash object for IPv4 packets going throught ECMP [sai_object_id_t] */
    SAI_ECMP_IPV4_HASH,

    /* The hash object for IPv4 in IPv4 packets going throught ECMP [sai_object_id_t] */
    SAI_ECMP_IPV4_IN_IPV4_HASH,

    /* The hash object for packets going throught LAG [sai_object_id_t] */
    SAI_LAG_HASH,

    /* The hash object for IPv4 packets going throught LAG [sai_object_id_t] */
    SAI_LAG_IPV4_HASH,

    /* The hash object for IPv4 in IPv4 packets going throught LAG [sai_object_id_t] */
    SAI_LAG_IPV4_IN_IPV4_HASH,

    ...

} sai_switch_attr_t;
~~~


### New Header saihash.h ###

*sai_hash_algorithm_t* defines the hash algorithms.

~~~cpp
/*
 * The sai hash algorithm
 */
typedef enum _sai_hash_algorithm_t
{
    /* Sai crc-based hash algorithm */
    SAI_HASH_ALGORITHM_CRC,

    /* Sai xor-based hash algorithm */
    SAI_HASH_ALGORITHM_XOR,

    /* Sai random-based hash algorithm */
    SAI_HASH_RANDOM,

} sai_hash_algorithm;
~~~

*sai_native_hash_field* defines the native hash fields.

~~~cpp
/*
 * The sai native hash fields
 */
typedef enum _sai_native_hash_field
{
    /* Sai native hash field source IP */
    SAI_NATIVE_HASH_FIELD_SRC_IP,

    /* Sai native hash field destination IP */
    SAI_NATIVE_HASH_FIELD_DST_IP,

    /* Sai native hash field vlan id */
    SAI_NATIVE_HASH_FIELD_VLAN_ID,

    /* Sai native hash field IP protocol */
    SAI_NATIVE_HASH_FIELD_IP_PROTOCOL,

    /* Sai native hash field ethernet type */
    SAI_NATIVE_HASH_FIELD_ETHERTYPE,

    /* Sai native hash field L4 source port */
    SAI_NATIVE_HASH_FIELD_L4_SRC_PORT,

    /* Sai native hash field L4 destination port */
    SAI_NATIVE_HASH_FIELD_L4_DST_PORT,

    /* Sai native hash field source MAC */
    SAI_NATIVE_HASH_FIELD_SRC_MAC,

    /* Sai native hash field destination MAC */
    SAI_NATIVE_HASH_FIELD_DST_MAC,

    /* Sai native hash field source port*/
    SAI_NATIVE_HASH_FIELD_IN_PORT,
    
    /* Sai native hash field destination port*/
    SAI_NATIVE_HASH_FIELD_OUT_PORT,

} sai_native_hash_field;
~~~

*sai_hash_attr_t* defines the hash attributes.

* SAI\_HASH\_ALGORITHM
    * Property: CREATE\_AND\_SET
    * Value Type: sai\_hash\_algorithm
    * Comment: Sai hash algorithm
* SAI\_HASH\_SEED,
    * Property: CREATE\_AND\_SET
    * Value Type: uint32\_t
    * Comment: Sai hash seed
* SAI\_HASH\_NATIVE\_FIELDS,
    * Property: CREATE\_AND\_SET
    * Value Type: sai\_u32\_list\_t(sai\_native\_hash\_field)
    * Comment: Sai hash native fields
* SAI\_HASH\_UDF\_FIELDS
    * Property: CREATE\_AND\_SET
    * Value Type: sai\_object\_list\_t(sai\_object\_id\_t)
    * Comment: Sai hash UDF fields

~~~cpp
/*
 *  Hash attribute IDs
 */
typedef enum _sai_hash_attr_t
{
    /* READ-ONLY */

    /* READ-WRITE */

    /* Sai hash algorithm [sai_hash_algorithm] (CREATE_AND_SET) (default to the value for SAI_HASH_DEFAULT_ALGORITHM in saiswitch) */
    SAI_HASH_ALGORITHM,

    /* Sai hash seed [uint32_t] (CREATE_AND_SET) (default to the value for SAI_DEFAULT_HASH_SEED in saiswitch) */
    SAI_HASH_SEED,

    /* Sai hash native fields [sai_u32_list_t(sai_native_hash_field)] (CREATE_AND_SET) (default to an empty list) */
    SAI_HASH_NATIVE_FIELDS,

    /* Sai hash UDF fields [sai_object_list_t(sai_object_id_t)] (CREATE_AND_SET) (default to an empty list) */
    SAI_HASH_UDF_FIELDS

} sai_hash_attr_t;
~~~

#### Create Hash ####

*sai_create_hash_fn* defines the interface to create Hash.

~~~cpp
/*
 * Routine Description:
 *    Create hash
 *
 * Arguments:
 *    [out] hash_id - hash id
 *    [in] attr_count - number of attributes
 *    [in] attr_list - array of attributes
 *
 * Return Values:
 *    SAI_STATUS_SUCCESS on success
 *    Failure status code on error
 */
typedef sai_status_t(*sai_create_hash_fn)(
    _Out_ sai_object_id_t* hash_id,
    _In_ uint32_t attr_count,
    _In_ sai_attribute_t *attr_list
    );
~~~

#### Remove Hash ####

*sai_remove_hash_fn* defines the interface to remove Hash.

~~~cpp
/*
 * Routine Description:
 *    Remove hash
 *
 * Arguments:
 *    [in] hash_id - hash id
 *
 * Return Values:
 *    SAI_STATUS_SUCCESS on success
 *    Failure status code on error
 */
typedef sai_status_t(*sai_remove_hash_fn)(
    _In_ sai_object_id_t hash_id
    );
~~~

#### Set Hash Attributes ####

*sai_set_hash_attribute_fn* defines the interface to set attributes for the Hash.

~~~cpp
/*
 * Routine Description:
 *    Set hash attribute
 *
 * Arguments:
 *    [in] hash_id - hash id
 *    [in] attr - attribute
 *
 * Return Values:
 *    SAI_STATUS_SUCCESS on success
 *    Failure status code on error
 */
typedef sai_status_t (*sai_set_hash_attribute_fn)(
    _In_ sai_object_id_t hash_id,
    _In_ const sai_attribute_t *attr
    );
~~~

#### Get Hash Attributes ####

*sai_get_hash_attribute_fn* defines the interface to get attributes for the Hash.

~~~cpp
/*
 * Routine Description:
 *    Get hash attribute
 *
 * Arguments:
 *    [in] hash_id - hash id
 *    [in] attr_count - number of attributes
 *    [inout] attr_list - array of attributes
 *
 * Return Values:
 *    SAI_STATUS_SUCCESS on success
 *    Failure status code on error
 */
typedef sai_status_t (*sai_get_hash_attribute_fn)(
    _In_ sai_object_id_t hash_id,
    _In_ uint32_t attr_count,
    _Inout_ sai_attribute_t *attr_list
    );
~~~

#### Hash API Table ####

*sai_hash_api_t* defines the Hash API table.

~~~cpp
/*
 *  Hash methods table retrieved with sai_api_query()
 */
typedef struct _sai_hash_api_t
{
    sai_create_hash_fn          create_hash;
    sai_remove_hash_fn          remove_hash;
    sai_set_hash_attribute_fn   set_hash_attribute;
    sai_get_hash_attribute_fn   get_hash_attribute;

} sai_hash_api_t;
~~~


## Example ##

### Get The Hash API Table ###

The following code shows how to get the hash API table:

~~~cpp
sai_hash_api_t* sai_hash_api;
if (sai_api_query(SAI_API_Hash, (void**)&sai_hash_api) == SAI_STATUS_SUCCESS)
{
    // Succeeded...
}
else
{
    // Failed...
}
~~~

### Create A Hash ###

The following code shows how to create a Hash:

~~~cpp
uint32_t hash_native_fields[4];
hash_native_fields[0] = SAI_NATIVE_HASH_FIELD_SRC_IP;
hash_native_fields[1] = SAI_NATIVE_HASH_FIELD_DST_IP;
hash_native_fields[2] = SAI_NATIVE_HASH_FIELD_L4_SRC_PORT;
hash_native_fields[3] = SAI_NATIVE_HASH_FIELD_L4_DST_PORT;

sai_object_id_t hash_id;
sai_attribute_t hash_attr;
hash_attr.id = (sai_attr_id_t)SAI_HASH_NATIVE_FIELDS;
hash_attr.value.u32list.list = hash_native_fields;
hash_attr.value.u32list.count = 4;

if (sai_hash_api->create_hash(&hash_id, 1, &hash_attr) == SAI_STATUS_SUCCESS)
{
    // Succeeded...
}
else
{
    // Failed...
}
~~~

### Remove A Hash Interface ###

The following code shows how to remove a Hash:

~~~cpp
if (sai_hash_api->remove_hash(hash_id) == SAI_STATUS_SUCCESS)
{
    // Succeeded...
}
else
{
    // Failed...
}
~~~

### Set Hash Interface Attributes ###

The following code shows how to set attributes to the Hash:

~~~cpp
uint32_t hash_native_fields[4];
hash_native_fields[0] = SAI_NATIVE_HASH_FIELD_SRC_IP;
hash_native_fields[1] = SAI_NATIVE_HASH_FIELD_DST_IP;
hash_native_fields[2] = SAI_NATIVE_HASH_FIELD_L4_SRC_PORT;
hash_native_fields[3] = SAI_NATIVE_HASH_FIELD_L4_DST_PORT;

sai_attribute_t hash_attr;
hash_attr.id = (sai_attr_id_t)SAI_HASH_NATIVE_FIELDS;
hash_attr.value.u32list.list = hash_native_fields;
hash_attr.value.u32list.count = 4;

if (sai_hash_api->set_hash_attribute(hash_id, &hash_attr) == SAI_STATUS_SUCCESS)
{
    // Succeeded...
}
else
{
    // Failed...
}
~~~

### Get Hash Interface Attributes ###

The following code shows how to get attributes to the Hash:

~~~cpp
sai_attribute_t hash_attr;
hash_attr.id = (sai_attr_id_t)SAI_HASH_NATIVE_FIELDS;

if (sai_hash_api->get_hash_attribute(hash_id, 1, &hash_attr) == SAI_STATUS_SUCCESS)
{
    // Succeeded...
}
else
{
    // Failed...
}
~~~


### Set Hash Object For Handling IPv4 Packets ###

The following code shows how to set hash object for handling ECMP IPv4 packets:

~~~cpp
sai_attribute_t switch_attr;
switch_attr.id = (sai_attr_id_t)SAI_ECMP_IPV4_HASH;
switch_attr.value.oid = hash_id;

if (sai_switch_api->set_switch_attribute(1, &switch_attr) == SAI_STATUS_SUCCESS)
{
    // Succeeded...
}
else
{
    // Failed...
}
~~~


