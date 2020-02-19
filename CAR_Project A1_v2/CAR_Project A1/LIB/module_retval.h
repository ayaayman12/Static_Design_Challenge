/*
 * module__retval.h
 *
 * Created: 2/12/2020 11:33:26 PM
 *  Author: A_ayman
 */ 


#ifndef MODULE_RETVAL_H_
#define MODULE_RETVAL_H_

/**
*   @brief:  This return value indicate that the function could
*             run successfully and it returns no errors.
*/
#define   E_NOK                                  ( 1 )
#define   E_OK                                   ( 0 )

#define   BCM_SUCCESS                            ( 0 )
/**
*   @brief:  This return value indicate that the selected resource
*           not found in the platform.
*/
#define   BCM_ERROR_RESOURCE_NOT_FOUND           ( -1 )
/**
*   @brief:  This return value indicate that the function tries
*             to use an uninitialized module.
*/
#define   BCM_ERROR_NOT_INITIALIZED              ( -2 )



#endif /* MODULE _RETVAL_H_*/