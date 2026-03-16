
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/SessionActorStartSessionRequestBody.h"
#include "BeamableCore/Public/AutoGen/ApiSessionsPostSessionResponse.h"

#include "PostSessionsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostSessionsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	USessionActorStartSessionRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostSessionsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Session|Utils|Make/Break", DisplayName="Make PostSessions",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Platform,_Device,_Source,_Locale,_Language,_CustomParams,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostSessionsRequest* Make(FOptionalString _Platform, FOptionalString _Device, FOptionalString _Source, FOptionalString _Locale, FOptionalSessionLanguageContextDto _Language, FOptionalMapOfString _CustomParams, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostSessionsSuccess, FBeamRequestContext, Context, UPostSessionsRequest*, Request, UApiSessionsPostSessionResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostSessionsError, FBeamRequestContext, Context, UPostSessionsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostSessionsComplete, FBeamRequestContext, Context, UPostSessionsRequest*, Request);

using FPostSessionsFullResponse = FBeamFullResponse<UPostSessionsRequest*, UApiSessionsPostSessionResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostSessionsFullResponse, FPostSessionsFullResponse);
