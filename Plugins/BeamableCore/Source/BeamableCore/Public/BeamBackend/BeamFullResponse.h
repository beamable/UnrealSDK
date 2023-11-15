#pragma once


#include "BeamRequestContext.h"
#include "BeamErrorResponse.h"
#include "RequestType.h"

#include "BeamFullResponse.generated.h"

UENUM(BlueprintType)
enum EBeamFullResponseState
{
	RS_Success,
	RS_Error,
	RS_Cancelled,
	RS_Retrying,
};

/**
 * @brief Templated wrapper for use in code ONLY WHEN YOU NEED LAMBDAS. ALWAYS PREFER THE BP COMPATIBLE VERSIONS!  
 */
template <typename TRequestData, typename TResponseData>
struct FBeamFullResponse
{
	/**
	 * @brief The request data that was sent to Beamable.
	 */
	TRequestData RequestData;

	/**
	 * @brief In case of success, the response body gets placed here.  
	 */
	TResponseData SuccessData;

	/**
	 * @brief In case of error, the response body gets placed here.
	 */
	FBeamErrorResponse ErrorData;

	/**
	 * @brief The internal RequestId. Users can use an API to cancel any request retry by passing this in. 
	 */
	FBeamRequestContext Context;

	/**
	 * @brief Whether or not the Beamable back-end responded successfully to the request. 
	 */
	EBeamFullResponseState State;

	/**
	 * @brief The current attempt number. Starts at 0.
	 */
	int AttemptNumber;
};

template <typename TRequestData, typename TResponseData>
using TBeamFullResponseHandler = TDelegate<void(FBeamFullResponse<TRequestData, TResponseData>)>;

template <typename TRequestData, typename TResponseData>
using TBlueprintRequestSuccessHandler = TBaseDynamicDelegate<FWeakObjectPtr, void, TRequestData, TResponseData>;

template <typename TRequestData>
using TBlueprintRequestErrorHandler = TBaseDynamicDelegate<FWeakObjectPtr, void, TRequestData, FBeamErrorResponse>;

template <typename TRequestData>
using TBlueprintRequestCompleteHandler = TBaseDynamicDelegate<FWeakObjectPtr, void, TRequestData>;
