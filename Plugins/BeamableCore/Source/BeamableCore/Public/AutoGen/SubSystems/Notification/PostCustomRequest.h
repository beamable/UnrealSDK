
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/NotificationRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "PostCustomRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostCustomRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UNotificationRequestBody* Body;

	// Beam Base Request Declaration
	UPostCustomRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_CustomChannelSuffix,_Dbid,_bUseSignalWhenPossible,_Dbids,Outer"))
	static UPostCustomRequest* MakePostCustomRequest(UNotificationRequestData* _Payload, FOptionalString _CustomChannelSuffix, FOptionalInt64 _Dbid, FOptionalBool _bUseSignalWhenPossible, FOptionalArrayOfInt64 _Dbids, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostCustomSuccess, FBeamRequestContext, Context, UPostCustomRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostCustomError, FBeamRequestContext, Context, UPostCustomRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostCustomComplete, FBeamRequestContext, Context, UPostCustomRequest*, Request);

using FPostCustomFullResponse = FBeamFullResponse<UPostCustomRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostCustomFullResponse, FPostCustomFullResponse);
