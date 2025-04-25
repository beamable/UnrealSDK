
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/GetLocalizationsResponse.h"

#include "GetLocalizationsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetLocalizationsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetLocalizationsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Content|Utils|Make/Break", DisplayName="Make GetLocalizations",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetLocalizationsRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetLocalizationsSuccess, FBeamRequestContext, Context, UGetLocalizationsRequest*, Request, UGetLocalizationsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetLocalizationsError, FBeamRequestContext, Context, UGetLocalizationsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetLocalizationsComplete, FBeamRequestContext, Context, UGetLocalizationsRequest*, Request);

using FGetLocalizationsFullResponse = FBeamFullResponse<UGetLocalizationsRequest*, UGetLocalizationsResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetLocalizationsFullResponse, FGetLocalizationsFullResponse);
