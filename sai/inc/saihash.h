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
 *    saihash.h
 *
 * Abstract:
 *
 *    This module defines SAI Hash API
 *
 */

#if !defined (__SAIHASH_H_)
#define __SAIHASH_H_

#include <saitypes.h>

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

#endif  // __SAIHASH_H_
