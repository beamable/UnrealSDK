
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/StartSessionRequestBody.h"
#include "BeamableCore/Public/AutoGen/StartSessionResponse.h"

#include "PostSessionRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostSessionRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UStartSessionRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostSessionRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Session|Utils|Make/Break", DisplayName="Make PostSession",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Source,_Shard,_Locale,_Language,_Time,_Platform,_Gamer,_Device,_CustomParams,_DeviceParams,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostSessionRequest* Make(FOptionalString _Source, FOptionalString _Shard, FOptionalString _Locale, FOptionalSessionLanguageContext _Language, FOptionalInt64 _Time, FOptionalString _Platform, FOptionalInt64 _Gamer, FOptionalString _Device, FOptionalMapOfString _CustomParams, FOptionalMapOfString _DeviceParams, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostSessionSuccess, FBeamRequestContext, Context, UPostSessionRequest*, Request, UStartSessionResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostSessionError, FBeamRequestContext, Context, UPostSessionRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostSessionComplete, FBeamRequestContext, Context, UPostSessionRequest*, Request);

using FPostSessionFullResponse = FBeamFullResponse<UPostSessionRequest*, UStartSessionResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostSessionFullResponse, FPostSessionFullResponse);
