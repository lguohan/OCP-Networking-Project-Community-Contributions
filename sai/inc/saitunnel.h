/*
 * Copyright (c) 2014 Microsoft Open Technologies, Inc.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License"); you may
 *    not use this file except in compliance with the License. You may obtain
 *    a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 *    THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR
 *    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 *    LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS
 *    FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT.
 *
 *    See the Apache Version 2.0 License for specific language governing
 *    permissions and limitations under the License.
 *
 *    Microsoft would like to thank the following companies for their review and
 *    assistance with these files: Intel Corporation, Mellanox Technologies Ltd,
 *    Dell Products, L.P., Facebook, Inc
 *
 * Module Name:
 *
 *    saitunnel.h
 *
 * Abstract:
 *
 *    This module defines SAI Tunnel API
 *
 */

#if !defined (__SAITUNNEL_H_)
#define __SAITUNNEL_H_

#include <saitypes.h>

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

/*
 *  Attribute id for tunnel operator
 */
typedef enum _sai_tunnel_operator_attr_t
{
    /* READ-ONLY */

    /* READ-WRITE */

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

#endif // __SAITUNNEL_H_
