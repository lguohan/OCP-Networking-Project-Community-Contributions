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
 *    saiudfgroup.h
 *
 * Abstract:
 *
 *    This module defines SAI UDF group
 *
 */

#if !defined (__SAIUDFGROUP_H_)
#define __SAIUDFGROUP_H_

#include <saitypes.h>

/*
 * Sai UDF type.
 */
typedef enum _sai_udf_group_type_t
{
    /* Sai generic UDF group */
    SAI_UDF_GROUP_GENERIC,

    /* Sai UDF group for hash */
    SAI_UDF_GROUP_HASH,

} sai_udf_group_type_t;

/*
 *  Attribute id for UDF group
 */
typedef enum _sai_udf_group_attr_t
{
    /* READ-ONLY */

    /* READ-WRITE */

    /* UDF group type [sai_udf_group_type_t] (CREATE_ONLY) (default to SAI_UDF_GENERIC) */
    SAI_UDF_GROUP_ATTR_TYPE,

} sai_udf_group_attr_t;

/*
 * Routine Description:
 *    Create UDF group
 *
 * Arguments:
 *    [out] udf_group_id - UDF group id
 *    [in] attr_count - number of attributes
 *    [in] attr_list - array of attributes
 *
 * Return Values:
 *    SAI_STATUS_SUCCESS on success
 *    Failure status code on error
 */
typedef sai_status_t (*sai_create_udf_group_fn)(
    _Out_ sai_object_id_t* udf_group_id,
    _In_ uint32_t attr_count,
    _In_ const sai_attribute_t *attr_list
    );

/*
 * Routine Description:
 *    Remove UDF group
 *
 * Arguments:
 *    [in] udf_group_id - UDF group id
 *
 * Return Values:
 *    SAI_STATUS_SUCCESS on success
 *    Failure status code on error
 */
typedef sai_status_t (*sai_remove_udf_group_fn)(
    _In_ sai_object_id_t udf_group_id
    );

/*
 * Routine Description:
 *    Set UDF group attribute
 *
 * Arguments:
 *    [in] sai_object_id_t - udf_group_id
 *    [in] attr - attribute
 *
 * Return Values:
 *    SAI_STATUS_SUCCESS on success
 *    Failure status code on error
 */
typedef sai_status_t (*sai_set_udf_group_attribute_fn)(
    _In_ sai_object_id_t udf_group_id,
    _In_ const sai_attribute_t *attr
    );

/*
 * Routine Description:
 *    Get UDF group attribute
 *
 * Arguments:
 *    [in] sai_object_id_t - udf_group_id
 *    [in] attr_count - number of attributes
 *    [inout] attr_list - array of attributes
 *
 * Return Values:
 *    SAI_STATUS_SUCCESS on success
 *    Failure status code on error
 */
typedef sai_status_t (*sai_get_udf_group_attribute_fn)(
    _In_ sai_object_id_t udf_group_id,
    _In_ uint32_t attr_count,
    _Inout_ sai_attribute_t *attr_list
    );

/*
 * Routine Description:
 *    Add UDF to a group
 *
 * Arguments:
 *    [in] udf_group_id - UDF group id
 *    [in] udf_count - number of UDFs
 *    [in] udfs - array of UDFs
 *
 * Return Values:
 *    SAI_STATUS_SUCCESS on success
 *    Failure status code on error
 */
typedef sai_status_t (*sai_add_udf_to_group_fn)(
    _In_ sai_object_id_t udf_group_id,
    _In_ uint32_t udf_count,
    _In_ const sai_object_id_t* udfs
    );

/*
 * Routine Description:
 *    Remove UDF from a group
 *
 * Arguments:
 *    [in] udf_group_id - UDF group id
 *    [in] udf_count - number of UDFs
 *    [in] udfs - array of UDFs
 *
 * Return Values:
 *    SAI_STATUS_SUCCESS on success
 *    Failure status code on error
 */
typedef sai_status_t (*sai_remove_udf_from_group_fn)(
    _In_ sai_object_id_t udf_group_id,
    _In_ uint32_t udf_count,
    _In_ const sai_object_id_t* udfs
    );

/*
 *  UDF group methods table retrieved with sai_api_query()
 */
typedef struct _sai_udf_group_api_t
{
    sai_create_udf_group_fn        create_udf_group;
    sai_remove_udf_group_fn        remove_udf_group;
    sai_set_udf_group_attribute_fn set_udf_group_attribute;
    sai_get_udf_group_attribute_fn get_udf_group_attribute;
    sai_add_udf_to_group_fn        add_udf_to_group;
    sai_remove_udf_from_group_fn   remove_udf_from_group;

} sai_udf_group_api_t;

#endif // __SAIUDFGROUP_H_
