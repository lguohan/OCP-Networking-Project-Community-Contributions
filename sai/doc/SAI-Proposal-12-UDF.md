SAI UDF (User Defined Field) Proposal
=====================

 Title       | SAI UDF (User Defined Field) Proposal
-------------|----------------------
 Authors     | Microsoft
 Status      | In review
 Type        | Standards track
 Created     | 04/16/2015
 SAI-Version | 0.9.3

---------

## Overview ##

UDF (User Defined Field) is a mechanism that enables users to extract customized fields of the packet. In SAI, UDF contains two parts, the matching rules and the extracting rules. The matching rules basically specify what packets can be used for this UDF. Once a packet matches the rules of a UDF, UDF uses its extracting rules to extract the data field of the data packet. 

## Specification ##

### Changes To sai.h ###

A new type **SAI_API_UDF** is added.

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
    SAI_API_UDF              = 14,  /* sai_udf_api_t */
} sai_api_t;
~~~


### New Header saiudf.h ###

#### UDF Type ####

*sai\_udf\_type\_t* defines the UDF type. Currently, there are two types supported, SAI\_UDF\_GENERIC and SAI\_UDF\_HASH. For hash UDFs, SAI\_UDF\_HASH must be specified. For other cases, SAI\_UDF\_GENERIC should be used, which is the default case.

~~~cpp
/*
 * Sai UDF type.
 */
typedef enum _sai_udf_type_t
{
    /* Sai generic UDF */
    SAI_UDF_GENERIC,

    /* Sai UDF for hash */
    SAI_UDF_HASH,

} sai_udf_type_t;
~~~

#### UDF Base ####

*sai\_udf\_base\_t* defines the base of the UDF. Valid options are SAI\_UDF\_BASE\_L2, SAI\_UDF\_BASE\_L3, SAI\_UDF\_BASE\_L4.

~~~cpp
/*
 * Sai UDF base
 */
typedef enum _sai_udf_base_t
{
    /* Sai UDF base L2 */
    SAI_UDF_BASE_L2,

    /* Sai UDF base L3 */
    SAI_UDF_BASE_L3,

    /* Sai UDF base L4 */
    SAI_UDF_BASE_L4,

} sai_udf_base_t;
~~~

#### UDF Attributes ####

*sai\_udf\_attr\_t* defines the UDF attributes. SAI\_UDF\_ATTR\_MATCH\_L2\_TYPE, SAI\_UDF\_ATTR\_MATCH\_L3\_TYPE and SAI\_UDF\_ATTR\_MATCH\_GRE\_TYPE define the matching rule. SAI\_UDF\_ATTR\_OFFSET and SAI\_UDF\_ATTR\_MASK defines the extracting rule.

* SAI\_UDF\_ATTR\_TYPE
    * Property: CREATE\_ONLY
    * Value Type: uint16\_t
    * Comment: UDF attribute type
* SAI\_UDF\_ATTR\_MATCH\_L2\_TYPE
    * Property: CREATE\_ONLY
    * Value Type: sai\_acl\_field\_data\_t(uint16\_t)
    * Comment: UDF L2 match rule
* SAI\_UDF\_ATTR\_MATCH\_L3\_TYPE
    * Property: CREATE\_ONLY
    * Value Type: sai\_acl\_field\_data\_t(uint16\_t)
    * Comment: UDF L3 match rule
* SAI\_UDF\_ATTR\_MATCH\_GRE\_TYPE
    * Property: CREATE\_ONLY
    * Value Type: sai\_acl\_field\_data\_t(uint16\_t)
    * Comment: UDF GRE match rule
* SAI\_UDF\_BASE
    * Property: CREATE\_AND\_SET
    * Value Type: sai\_udf\_base\_t
    * Comment: UDF baes
* SAI\_UDF\_ATTR\_OFFSET
    * Property: MANDATORY\_ON\_CREATE | CREATE\_AND\_SET
    * Value Type: uint16\_t
    * Comment: UDF offset
* SAI\_UDF\_ATTR\_MASK
    * Property: MANDATORY\_ON\_CREATE | CREATE\_AND\_SET
    * Value Type: uint16\_t
    * Comment: UDF mask


~~~cpp
/*
 *  Attribute id for UDF
 */
typedef enum _sai_udf_attr_t
{
    /* READ-ONLY */

    /* READ-WRITE */

    /* UDF type [sai_udf_type_t] (CREATE_ONLY) (default to SAI_UDF_GENERIC) */
    SAI_UDF_ATTR_TYPE,

    /* UDF L2 match rule [sai_acl_field_data_t(uint16_t)] (CREATE_ONLY) (default to None) */
    SAI_UDF_ATTR_MATCH_L2_TYPE,

    /* UDF L3 match rule [sai_acl_field_data_t(uint8_t)] (CREATE_ONLY) (default to None) */
    SAI_UDF_ATTR_MATCH_L3_TYPE,

    /* UDF GRE match rule [sai_acl_field_data_t(uint16_t)] (CREATE_ONLY) (default to None) */
    SAI_UDF_ATTR_MATCH_GRE_TYPE,

    /* UDF base [sai_udf_base_t] (CREATE_AND_SET) (default to SAI_UDF_BASE_L2) */
    SAI_UDF_ATTR_BASE,

    /* UDF byte offset [uint16_t] (MANDATORY_ON_CREATE|CREATE_AND_SET) */
    SAI_UDF_ATTR_OFFSET,

    /* UDF byte length [uint16_t] (MANDATORY_ON_CREATE|CREATE_AND_SET) */
    SAI_UDF_ATTR_LENGTH,

} sai_udf_attr_t;
~~~

#### Create UDF ####

*sai_create_udf_fn* defines the interface to create UDF.

~~~cpp
/*
 * Routine Description:
 *    Create UDF
 *
 * Arguments:
 *    [out] udf_id - UDF id
 *    [in] attr_count - number of attributes
 *    [in] attr_list - array of attributes
 *
 * Return Values:
 *    SAI_STATUS_SUCCESS on success
 *    Failure status code on error
 */
typedef sai_status_t (*sai_create_udf_fn)(
    _Out_ sai_object_id_t* udf_id,
    _In_ uint32_t attr_count,
    _In_ const sai_attribute_t *attr_list
    );
~~~

#### Remove UDF ####

*sai_remove_udf_fn* defines the interface to remove UDF.

~~~cpp
/*
 * Routine Description:
 *    Remove UDF
 *
 * Arguments:
 *    [in] udf_id - UDF id
 *
 * Return Values:
 *    SAI_STATUS_SUCCESS on success
 *    Failure status code on error
 */
typedef sai_status_t (*sai_remove_udf_fn)(
    _In_ sai_object_id_t udf_id
    );
~~~

#### Set UDF Attributes ####

*sai_set_udf_attribute_fn* defines the interface to set attributes for the UDF.

~~~cpp
/*
 * Routine Description:
 *    Set UDF attribute
 *
 * Arguments:
 *    [in] sai_object_id_t - udf_id
 *    [in] attr - attribute
 *
 * Return Values:
 *    SAI_STATUS_SUCCESS on success
 *    Failure status code on error
 */
typedef sai_status_t (*sai_set_udf_attribute_fn)(
    _In_ sai_object_id_t udf_id,
    _In_ const sai_attribute_t *attr
    );
~~~

#### Get UDF Attributes ####

*sai_get_udf_attribute_fn* defines the interface to get attributes for the UDF.

~~~cpp
/*
 * Routine Description:
 *    Get UDF attribute
 *
 * Arguments:
 *    [in] sai_object_id_t - udf_id
 *    [in] attr_count - number of attributes
 *    [inout] attr_list - array of attributes
 *
 * Return Values:
 *    SAI_STATUS_SUCCESS on success
 *    Failure status code on error
 */
typedef sai_status_t (*sai_get_udf_attribute_fn)(
    _In_ sai_object_id_t udf_id,
    _In_ uint32_t attr_count,
    _Inout_ sai_attribute_t *attr_list
    );
~~~

#### UDF API Table ####

*sai_udf_api_t* defines the UDF API table.

~~~cpp
/*
 *  UDF methods table retrieved with sai_api_query()
 */
typedef struct _sai_udf_api_t
{
    sai_create_udf_fn        create_udf;
    sai_remove_udf_fn        remove_udf;
    sai_set_udf_attribute_fn set_udf_attribute;
    sai_get_udf_attribute_fn get_udf_attribute;

} sai_udf_api_t;
~~~


## Example ##

### Get The UDF API Table ###

The following code shows how to get the UDF API table:

~~~cpp
sai_udf_api_t* sai_udf_api;
if (sai_api_query(SAI_API_UDF, (void**)&sai_udf_api) == SAI_STATUS_SUCCESS)
{
    // Succeeded...
}
else
{
    // Failed...
}
~~~

### Create A UDF Interface ###

The following code shows how to create a UDF to extract the TCP flags:

~~~cpp
sai_object_id_t udf_id;
sai_attribute_t udf_attrs[4];
udf_attrs[0].id = (sai_attr_id_t)SAI_UDF_ATTR_MATCH_L2_TYPE;
udf_attrs[0].value.u16 = 0x0800;
udf_attrs[1].id = (sai_attr_id_t)SAI_UDF_ATTR_MATCH_L3_TYPE;
udf_attrs[1].value.u16 = 0x0600;
udf_attrs[2].id = (sai_attr_id_t)SAI_UDF_ATTR_OFFSET;
udf_attrs[2].value.u16 = 47;
udf_attrs[3].id = (sai_attr_id_t)SAI_UDF_ATTR_LENGTH;
udf_attrs[3].value.u16 = 1;

if (sai_udf_api->create_udf(&udf_id, 4, udf_attrs) == SAI_STATUS_SUCCESS)
{
    // Succeeded...
}
else
{
    // Failed...
}
~~~

### Remove A UDF Interface ###

The following code shows how to remove a UDF:

~~~cpp
if (sai_udf_api->remove_udf(udf_id) == SAI_STATUS_SUCCESS)
{
    // Succeeded...
}
else
{
    // Failed...
}
~~~

### Set UDF Interface Attributes ###

The following code shows how to set attributes to the UDF:

~~~cpp
sai_attribute_t udf_attr;
udf_attr.id = (sai_attr_id_t)SAI_UDF_ATTR_OFFSET;
udf_attr.value.u16 = 47;

if (sai_udf_api->set_udf_attribute(&udf_id, &udf_attr) == SAI_STATUS_SUCCESS)
{
    // Succeeded...
}
else
{
    // Failed...
}
~~~

### Get UDF Interface Attributes ###

The following code shows how to get attributes to the UDF:

~~~cpp
sai_attribute_t udf_attrs[2];
udf_attrs[0].id = (sai_attr_id_t)SAI_UDF_ATTR_OFFSET;
udf_attrs[1].id = (sai_attr_id_t)SAI_UDF_ATTR_MASK;

if (sai_udf_api->get_udf_attribute(&udf_id, 2, udf_attrs) == SAI_STATUS_SUCCESS)
{
    // Succeeded...
}
else
{
    // Failed...
}
~~~
