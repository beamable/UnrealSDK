
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/NotificationRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "PostPlayerRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostPlayerRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UNotificationRequestBody* Body;

	// Beam Base Request Declaration
	UPostPlayerRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_CustomChannelSuffix,_Dbid,_bUseSignalWhenPossible,_Dbids,Outer"))
	static UPostPlayerRequest* MakePostPlayerRequest(UNotificationRequestData* _Payload, FOptionalString _CustomChannelSuffix, FOptionalInt64 _Dbid, FOptionalBool _bUseSignalWhenPossible, FOptionalArrayOfInt64 _Dbids, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostPlayerSuccess, FBeamRequestContext, Context, UPostPlayerRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostPlayerError, FBeamRequestContext, Context, UPostPlayerRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostPlayerComplete, FBeamRequestContext, Context, UPostPlayerRequest*, Request);

using FPostPlayerFullResponse = FBeamFullResponse<UPostPlayerRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostPlayerFullResponse, FPostPlayerFullResponse);
