
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/NotificationRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PostGenericRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostGenericRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UNotificationRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostGenericRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Notification|Utils|Make/Break", DisplayName="Make PostGeneric",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bUseSignalWhenPossible,_CustomChannelSuffix,_Dbid,_Dbids,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostGenericRequest* Make(UNotificationRequestData* _Payload, FOptionalBool _bUseSignalWhenPossible, FOptionalString _CustomChannelSuffix, FOptionalInt64 _Dbid, FOptionalArrayOfInt64 _Dbids, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostGenericSuccess, FBeamRequestContext, Context, UPostGenericRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostGenericError, FBeamRequestContext, Context, UPostGenericRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostGenericComplete, FBeamRequestContext, Context, UPostGenericRequest*, Request);

using FPostGenericFullResponse = FBeamFullResponse<UPostGenericRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostGenericFullResponse, FPostGenericFullResponse);
