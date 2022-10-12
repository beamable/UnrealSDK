
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/NotificationRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "BasicNotificationPostGameRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicNotificationPostGameRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UNotificationRequestBody* Body;

	// Beam Base Request Declaration
	UBasicNotificationPostGameRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_CustomChannelSuffix,_Dbid,_bUseSignalWhenPossible,_Dbids,Outer"))
	static UBasicNotificationPostGameRequest* MakeBasicNotificationPostGameRequest(UNotificationRequestData* _Payload, FOptionalString _CustomChannelSuffix, FOptionalInt64 _Dbid, FOptionalBool _bUseSignalWhenPossible, FOptionalArrayOfInt64 _Dbids, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicNotificationPostGameSuccess, FBeamRequestContext, Context, UBasicNotificationPostGameRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicNotificationPostGameError, FBeamRequestContext, Context, UBasicNotificationPostGameRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicNotificationPostGameComplete, FBeamRequestContext, Context, UBasicNotificationPostGameRequest*, Request);

using FBasicNotificationPostGameFullResponse = FBeamFullResponse<UBasicNotificationPostGameRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicNotificationPostGameFullResponse, FBasicNotificationPostGameFullResponse);
