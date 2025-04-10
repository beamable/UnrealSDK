
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/GetLogsUrlRequestBody.h"
#include "BeamableCore/Public/AutoGen/GetSignedUrlResponse.h"

#include "PostLogsUrlRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostLogsUrlRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UGetLogsUrlRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostLogsUrlRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make PostLogsUrl",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_StartTime,_NextToken,_Filter,_EndTime,_Limit,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostLogsUrlRequest* Make(FString _ServiceName, FOptionalInt64 _StartTime, FOptionalString _NextToken, FOptionalString _Filter, FOptionalInt64 _EndTime, FOptionalInt32 _Limit, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostLogsUrlSuccess, FBeamRequestContext, Context, UPostLogsUrlRequest*, Request, UGetSignedUrlResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostLogsUrlError, FBeamRequestContext, Context, UPostLogsUrlRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostLogsUrlComplete, FBeamRequestContext, Context, UPostLogsUrlRequest*, Request);

using FPostLogsUrlFullResponse = FBeamFullResponse<UPostLogsUrlRequest*, UGetSignedUrlResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostLogsUrlFullResponse, FPostLogsUrlFullResponse);
