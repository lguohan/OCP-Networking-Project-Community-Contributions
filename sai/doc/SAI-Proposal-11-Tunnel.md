SAI Tunnel Interface Proposal
=====================

 Title       | SAI tunnel interface
-------------|----------------------
 Authors     | Microsoft
 Status      | In review
 Type        | Standards track
 Created     | 04/03/2015
 SAI-Version | 0.9.2

---------

## Overview ##

Tunnel is an network channel that enables communications between two network devices. Typically, tunnel is implemented by packet encapsulation.
For example, encapsulating a packet with an IP header whose IP destination is A, enables the packet goes to A, no matter what is the original IP destination in the packet, just like the packet is going through a channel.

In SAI, tunnel is created by creating two **tunnel operators** at each end of the tunnel. At the beginning of the tunnel, we create a **a tunnel initiator**. At the end of the tunnel we create **a tunnel terminator**. (If one end of the tunnel is a server, instead of a switch, it does not need to create a tunnel initiator or a tunnel initiator. We depends on softwares for the packet encapsulation and decapsulation. In the following of this document, we ignore the case that either end is a server.)

A tunnel initiator is the beginning of a tunnel. Every packet goes into a tunnel from the tunnel initiator. A tunnel initiator is bound to a router interface. Whenever a packet goes to the router interface, the packet goes into the tunnel. The tunnel initiator contains enough information to fill up the encap header. For example, first of all, it contains the encap header type, e.g., an IPv4 header or an IPv6 header. If it is an IPv4 header, it will have to contain the information for the source IP address, the destination IP address, the TTL, the DSCP value, etc.

A tunnel terminator is the end of a tunnel. Every packet goes out of a tunnel from the tunnel terminator. A tunnel terminator is not bound to a specific router interface. Every packet goes into the switch will pass the tunnel terminator. If the packet header matches the tunnel information (<span style="color:red">To be more accurate here</span>). The tunnel header will be decapsulated. A tunnel terminator also contains the information of the tunnel type, the source IP address, the destination IP address, the TTL and the DSCP value, etc.

## Specification ##

### Changes To sai.h ###

A new type **SAI_API_TUNNEL** is added.

<pre>
<code>
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
<span style="color:red">    SAI_API_TUNNEL           = 14,  /* sai_tunnel_api_t */</span>
} sai_api_t;
</code>
</pre>

### Changes To saitypes.h ###

A new attribute value type, **sai_object_id_t**, is added.

<pre>
<code>
/*
 * Data Type to use enum's as attribute value is sai_int32_t s32
 *
 */
typedef union {
    bool booldata;
    char chardata[32];
    sai_uint8_t u8;
    sai_int8_t s8;
    sai_uint16_t u16;
    sai_int16_t s16;
    sai_uint32_t u32;
    sai_int32_t s32;
    sai_uint64_t u64;
    sai_int64_t s64;
    sai_mac_t mac;
    sai_ip4_t ip4;
    sai_ip6_t ip6;
    sai_ip_address_t ipaddr;
<span style="color:red">    sai_object_id_t intf;</span>
    sai_object_list_t objlist;
    sai_acl_field_data_t aclfield;
    sai_acl_action_data_t acldata;
} sai_attribute_value_t;
</code>
</pre>

### New Header saitunnel.h ###

#### Tunnel Operator Type ####

*sai_tunnel_operator_type_t* defines the types of the tunnel. More specifically, it specifies the type of the encapsulated header. Currently, IPv4 and IPv6 are supported.

<pre>
<code>
/*
 * Tunnel operator type, i.e., the type of the encapped header
 */
typedef enum _sai_tunnel_operator_type_t
{
    /* Sai tunnel operator IPv4 */
    SAI_TUNNEL_OPERATOR_IPV4,

    /* Sai tunnel operator IPv6 */
    SAI_TUNNEL_OPERATOR_IPV6,

} sai_tunnel_operator_type_t;
</code>
</pre>

#### Tunnel Operator Attribute ####

*sai_tunnel_operator_attr_t* defines the tunnel operator attributes.

* SAI\_TUNNEL\_OPERATOR\_ATTR\_INTF [MANDATORY\_ON\_CREATE | CREATE\_ONLY]: Tunnel operator interface. This is only useful for a tunnel terminator.
* SAI\_TUNNEL\_OPERATOR\_ATTR\_TYPE [MANDATORY\_ON\_CREATE | CREATE\_AND\_SET]: Tunnel operator type.
* SAI\_TUNNEL\_OPERATOR\_ATTR\_SIP [MANDATORY\_ON\_CREATE | CREATE\_AND\_SET]: Tunnel operator source ip address.
* SAI\_TUNNEL\_OPERATOR\_ATTR\_DIP [MANDATORY\_ON\_CREATE | CREATE\_AND\_SET]: Tunnel operator destination ip address.
* SAI\_TUNNEL\_OPERATOR\_ATTR\_TTL [CREATE\_AND\_SET]: Tunnel operator ttl, the default value is 64.
* SAI\_TUNNEL\_OPERATOR\_ATTR\_DSCP [CREATE\_AND\_SET]: Tunnel operator dscp, the default value is 0.
* SAI\_TUNNEL\_OPERATOR\_ATTR\_IPV6\_FLOW\_LABEL [CREATE\_AND\_SET]: Tunnel operator IPv6 flow label, the default value is 0.

<pre>
<code>
/*
 *  Attribute id for tunnel operator
 */
typedef enum _sai_tunnel_operator_attr_t
{
    /* Tunnel operator interface. This is only useful for a tunnel terminator [sai_object_id_t] (MANDATORY_ON_CREATE|CREATE_ONLY) */
    SAI_TUNNEL_OPERATOR_ATTR_INTF,

    /* Tunnel operator type [sai_tunnel_operator_type_t] (MANDATORY_ON_CREATE|CREATE_AND_SET) */
    SAI_TUNNEL_OPERATOR_ATTR_TYPE,

    /* Tunnel operator source ip address [sai_ip_address_t] (MANDATORY_ON_CREATE|CREATE_AND_SET) */
    SAI_TUNNEL_OPERATOR_ATTR_SIP,

    /* Tunnel operator destination ip address [sai_ip_address_t] (MANDATORY_ON_CREATE|CREATE_AND_SET) */
    SAI_TUNNEL_OPERATOR_ATTR_DIP,

    /* Tunnel operator ttl [uint8_t] (CREATE_AND_SET) (default to 64) */
    SAI_TUNNEL_OPERATOR_ATTR_TTL,

    /* Tunnel operator dscp [uint8_t] (CREATE_AND_SET) (default to 0) */
    SAI_TUNNEL_OPERATOR_ATTR_DSCP,

    /* Tunnel operator IPv6 flow label [uint32_t] (CREATE_AND_SET) (default to 0) */
    SAI_TUNNEL_OPERATOR_ATTR_IPV6_FLOW_LABEL,

} sai_tunnel_operator_attr_t;
</code>
</pre>


#### Create Tunnel Operator ####

*sai_create_tunnel_operator_fn* defines the interface to create tunnel operator.

<pre>
<code>
/*
 * Routine Description:
 *    Create tunnel operator
 *
 * Arguments:
 *    [out] tunnel_operator_id - tunnel id
 *    [in] attr_count - number of attributes
 *    [in] attr_list - array of attributes
 *
 * Return Values:
 *    SAI_STATUS_SUCCESS on success
 *    Failure status code on error
 */
typedef sai_status_t (*sai_create_tunnel_operator_fn)(
    _Out_ sai_object_id_t* tunnel_operator_id,
    _In_ uint32_t attr_count,
    _In_ const sai_attribute_t *attr_list
    );
</code>
</pre>

#### Remove Tunnel Operator ####

*sai_remove_tunnel_operator_fn* defines the interface to remove tunnel operator.

<pre>
<code>
/*
 * Routine Description:
 *    Remove tunnel operator
 *
 * Arguments:
 *    [in] tunnel_operator_id - tunnel id
 *
 * Return Values:
 *    SAI_STATUS_SUCCESS on success
 *    Failure status code on error
 */
typedef sai_status_t (*sai_remove_tunnel_operator_fn)(
    _In_ sai_object_id_t tunnel_operator_id
    );
</code>
</pre>

#### Set Tunnel Operator Attributes ####

*sai_set_tunnel_operator_attribute_fn* defines the interface to set attributes for the tunnel operator.

<pre>
<code>
/*
 * Routine Description:
 *    Set tunnel operator attribute
 *
 * Arguments:
 *    [in] sai_object_id_t - tunnel_operator_id
 *    [in] attr - attribute
 *
 * Return Values:
 *    SAI_STATUS_SUCCESS on success
 *    Failure status code on error
 */
typedef sai_status_t (*sai_set_tunnel_operator_attribute_fn)(
    _In_ sai_object_id_t tunnel_operator_id,
    _In_ const sai_attribute_t *attr
    );
</code>
</pre>

#### Get Tunnel Operator Attributes ####

*sai_get_tunnel_operator_attribute_fn* defines the interface to get attributes for the tunnel operator.

<pre>
<code>
/*
 * Routine Description:
 *    Get tunnel operator attribute
 *
 * Arguments:
 *    [in] sai_object_id_t - tunnel_operator_id
 *    [in] attr_count - number of attributes
 *    [inout] attr_list - array of attributes
 *
 * Return Values:
 *    SAI_STATUS_SUCCESS on success
 *    Failure status code on error
 */
typedef sai_status_t (*sai_get_tunnel_operator_attribute_fn)(
    _In_ sai_object_id_t tunnel_operator_id,
    _In_ uint32_t attr_count,
    _Inout_ sai_attribute_t *attr_list
    );
</code>
</pre>

#### Tunnel API Table ####

*sai_tunnel_api_t* defines the tunnel API table.

<pre>
<code>
/*
 *  Tunnel methods table retrieved with sai_api_query()
 */
typedef struct _sai_tunnel_api_t
{
    sai_create_tunnel_operator_fn        create_tunnel_initiator;
    sai_remove_tunnel_operator_fn        remove_tunnel_initiator;
    sai_create_tunnel_operator_fn        create_tunnel_terminator;
    sai_remove_tunnel_operator_fn        remove_tunnel_terminator;
    sai_set_tunnel_operator_attribute_fn set_tunnel_operator_attribute;
    sai_get_tunnel_operator_attribute_fn get_tunnel_operator_attribute;

} sai_tunnel_api_t;
</code>
</pre>


## Example ##

### Get The Tunnel API Table ###

The following code shows how to get the tunnel API table:

<pre>
<code>
sai_tunnel_api_t* sai_tunnel_api;
sai_api_query(SAI_API_TUNNEL, (void**)&sai_tunnel_api);
</code>
</pre>

### Create A Tunnel Initiator ###

The following code shows how to create a tunnel initiator:

<pre>
<code>
sai_object_id_t tunnel_initiator_id;
sai_attribute_t tunnel_attrs[4];
tunnel_attrs[0].id = (sai_attr_id_t)SAI_TUNNEL_ATTR_INTF;
tunnel_attrs[0].value.ipaddr = intf;
tunnel_attrs[1].id = (sai_attr_id_t)SAI_TUNNEL_ATTR_TYPE;
tunnel_attrs[1].value.u32 = (sai_uint32_t)SAI_TUNNEL_IPv4;
tunnel_attrs[2].id = (sai_attr_id_t)SAI_TUNNEL_ATTR_SIP;
tunnel_attrs[2].value.ipaddr = ntohl(sip.addr());
tunnel_attrs[3].id = (sai_attr_id_t)SAI_TUNNEL_ATTR_DIP;
tunnel_attrs[3].value.ipaddr = ntohl(dip.addr());

if (sai_tunnel_api->create_tunnel_initiator(&tunnel_initiator_id, tunnel_attrs, 4) == SAI_STATUS_SUCCESS))
{
    // Succeeded...
}
else
{
    // Failed...
}
</code>
</pre>

### Create A Tunnel Terminator ###

The following code shows how to create a tunnel terminator:

<pre>
<code>
sai_object_id_t tunnel_terminator_id;
sai_attribute_t tunnel_attrs[3];
tunnel_attrs[0].id = (sai_attr_id_t)SAI_TUNNEL_ATTR_TYPE;
tunnel_attrs[0].value.u32 = (sai_uint32_t)SAI_TUNNEL_IPv4;
tunnel_attrs[1].id = (sai_attr_id_t)SAI_TUNNEL_ATTR_SIP;
tunnel_attrs[1].value.ipaddr = ntohl(sip.addr());
tunnel_attrs[2].id = (sai_attr_id_t)SAI_TUNNEL_ATTR_DIP;
tunnel_attrs[2].value.ipaddr = ntohl(dip.addr());

if (sai_tunnel_api->create_tunnel_terminator(&tunnel_terminator_id, tunnel_attrs, 3) == SAI_STATUS_SUCCESS))
{
    // Succeeded...
}
else
{
    // Failed...
}
</code>
</pre>

### Remove A Tunnel Initiator And Terminator ###

The following code shows how to remove a tunnel initiator and terminator:

<pre>
<code>
if (sai_tunnel_api->remove_tunnel_initiator(tunnel_initiator_id) == SAI_STATUS_SUCCESS))
{
    // Succeeded...
}
else
{
    // Failed...
}

if (sai_tunnel_api->remove_tunnel_terminator(tunnel_terminator_id) == SAI_STATUS_SUCCESS))
{
    // Succeeded...
}
else
{
    // Failed...
}
</code>
</pre>

### Set Tunnel Operator Attributes ###

The following code shows how to set attributes to the tunnel operator:

<pre>
<code>
sai_attribute_t tunnel_attrs[2];
tunnel_attrs[0].id = (sai_attr_id_t)SAI_TUNNEL_OPERATOR_ATTR_TTL;
tunnel_attrs[0].value.u8 = 128;
tunnel_attrs[1].id = (sai_attr_id_t)SAI_TUNNEL_OPERATOR_ATTR_DSCP;
tunnel_attrs[1].value.u8 = 1;

if (sai_tunnel_api->set_tunnel_operator_attribute(&tunnel_operator_id, tunnel_attrs, 2) == SAI_STATUS_SUCCESS))
{
    // Succeeded...
}
else
{
    // Failed...
}
</code>
</pre>

### Get Tunnel Operator Attributes ###

The following code shows how to get attributes to the tunnel operator:

<pre>
<code>
sai_attribute_t tunnel_attrs[2];
tunnel_attrs[0].id = (sai_attr_id_t)SAI_TUNNEL_OPERATOR_ATTR_TTL;
tunnel_attrs[1].id = (sai_attr_id_t)SAI_TUNNEL_OPERATOR_ATTR_DSCP;

if (sai_tunnel_api->get_tunnel_operator_attribute(&tunnel_operator_id, tunnel_attrs, 2) == SAI_STATUS_SUCCESS))
{
    // Succeeded...
}
else
{
    // Failed...
}
</code>
</pre>
