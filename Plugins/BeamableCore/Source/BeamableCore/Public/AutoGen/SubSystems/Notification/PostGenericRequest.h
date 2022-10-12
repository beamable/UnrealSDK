
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/NotificationRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "PostGenericRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostGenericRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UNotificationRequestBody* Body;

	// Beam Base Request Declaration
	UPostGenericRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_CustomChannelSuffix,_Dbid,_bUseSignalWhenPossible,_Dbids,Outer"))
	static UPostGenericRequest* MakePostGenericRequest(UNotificationRequestData* _Payload, FOptionalString _CustomChannelSuffix, FOptionalInt64 _Dbid, FOptionalBool _bUseSignalWhenPossible, FOptionalArrayOfInt64 _Dbids, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostGenericSuccess, FBeamRequestContext, Context, UPostGenericRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostGenericError, FBeamRequestContext, Context, UPostGenericRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostGenericComplete, FBeamRequestContext, Context, UPostGenericRequest*, Request);

using FPostGenericFullResponse = FBeamFullResponse<UPostGenericRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostGenericFullResponse, FPostGenericFullResponse);
