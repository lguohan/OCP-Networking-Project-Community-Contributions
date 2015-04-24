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
 *    saiudfmatch.h
 *
 * Abstract:
 *
 *    This module defines SAI UDF match
 *
 */

#if !defined (__SAIUDFMATCH_H_)
#define __SAIUDFMATCH_H_

#include <saitypes.h>

/*
 *  Attribute id for UDF match
 */
typedef enum _sai_udf_match_attr_t
{
    /* READ-ONLY */

    /* READ-WRITE */

    /* UDF L2 match rule [sai_acl_field_data_t(uint16_t)] (CREATE_ONLY) (default to None) */
    SAI_UDF_MATCH_ATTR_L2_TYPE,

    /* UDF L3 match rule [sai_acl_field_data_t(uint8_t)] (CREATE_ONLY) (default to None) */
    SAI_UDF_MATCH_ATTR_L3_TYPE,

    /* UDF GRE match rule [sai_acl_field_data_t(uint16_t)] (CREATE_ONLY) (default to None) */
    SAI_UDF_MATCH_ATTR_GRE_TYPE,

    /* UDF match priority [uint8_t] (CREATE_ONLY) (default to 0) */
    SAI_UDF_MATCH_ATTR_PRIORITY

} sai_udf_match_attr_t;

/*
 * Routine Description:
 *    Create UDF match
 *
 * Arguments:
 *    [out] udf_match_id - UDF match id
 *    [in] attr_count - number of attributes
 *    [in] attr_list - array of attributes
 *
 * Return Values:
 *    SAI_STATUS_SUCCESS on success
 *    Failure status code on error
 */
typedef sai_status_t (*sai_create_udf_match_fn)(
    _Out_ sai_object_id_t* udf_match_id,
    _In_ uint32_t attr_count,
    _In_ const sai_attribute_t *attr_list
    );

/*
 * Routine Description:
 *    Remove UDF match
 *
 * Arguments:
 *    [in] udf_match_id - UDF match id
 *
 * Return Values:
 *    SAI_STATUS_SUCCESS on success
 *    Failure status code on error
 */
typedef sai_status_t (*sai_remove_udf_match_fn)(
    _In_ sai_object_id_t udf_match_id
    );

/*
 * Routine Description:
 *    Set UDF match attribute
 *
 * Arguments:
 *    [in] sai_object_id_t - udf_match_id
 *    [in] attr - attribute
 *
 * Return Values:
 *    SAI_STATUS_SUCCESS on success
 *    Failure status code on error
 */
typedef sai_status_t (*sai_set_udf_match_attribute_fn)(
    _In_ sai_object_id_t udf_match_id,
    _In_ const sai_attribute_t *attr
    );

/*
 * Routine Description:
 *    Get UDF match attribute
 *
 * Arguments:
 *    [in] sai_object_id_t - udf_match_id
 *    [in] attr_count - number of attributes
 *    [inout] attr_list - array of attributes
 *
 * Return Values:
 *    SAI_STATUS_SUCCESS on success
 *    Failure status code on error
 */
typedef sai_status_t (*sai_get_udf_match_attribute_fn)(
    _In_ sai_object_id_t udf_match_id,
    _In_ uint32_t attr_count,
    _Inout_ sai_attribute_t *attr_list
    );

/*
 *  UDF match methods table retrieved with sai_api_query()
 */
typedef struct _sai_udf_match_api_t
{
    sai_create_udf_match_fn        create_udf_match;
    sai_remove_udf_match_fn        remove_udf_match;
    sai_set_udf_match_attribute_fn set_udf_match_attribute;
    sai_get_udf_match_attribute_fn get_udf_match_attribute;

} sai_udf_match_api_t;

#endif // __SAIUDF matchMATCH_H_
