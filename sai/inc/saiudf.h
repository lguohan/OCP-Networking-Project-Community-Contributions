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
 *    saiudf.h
 *
 * Abstract:
 *
 *    This module defines SAI UDF (User Defined Field)
 *
 */

#if !defined (__SAIUDF_H_)
#define __SAIUDF_H_

#include <saitypes.h>

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

    /* UDF L3 match rule [sai_acl_field_data_t(uint16_t)] (CREATE_ONLY) (default to None) */
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

#endif // __SAIUDF_H_
