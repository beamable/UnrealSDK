
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/GetLogsUrlRequestBody.h"
#include "AutoGen/GetSignedUrlResponse.h"

#include "PostLogsUrlRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostLogsUrlRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UGetLogsUrlRequestBody* Body;

	// Beam Base Request Declaration
	UPostLogsUrlRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_StartTime,_NextToken,_Filter,_EndTime,_Limit,Outer"))
	static UPostLogsUrlRequest* MakePostLogsUrlRequest(FOptionalInt64 _StartTime, FString _ServiceName, FOptionalString _NextToken, FOptionalString _Filter, FOptionalInt64 _EndTime, FOptionalInt32 _Limit, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostLogsUrlSuccess, FBeamRequestContext, Context, UPostLogsUrlRequest*, Request, UGetSignedUrlResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostLogsUrlError, FBeamRequestContext, Context, UPostLogsUrlRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostLogsUrlComplete, FBeamRequestContext, Context, UPostLogsUrlRequest*, Request);

using FPostLogsUrlFullResponse = FBeamFullResponse<UPostLogsUrlRequest*, UGetSignedUrlResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostLogsUrlFullResponse, FPostLogsUrlFullResponse);