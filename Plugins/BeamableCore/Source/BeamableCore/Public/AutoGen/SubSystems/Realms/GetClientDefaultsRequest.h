
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/RealmConfiguration.h"

#include "GetClientDefaultsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetClientDefaultsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetClientDefaultsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make GetClientDefaults",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetClientDefaultsRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetClientDefaultsSuccess, FBeamRequestContext, Context, UGetClientDefaultsRequest*, Request, URealmConfiguration*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetClientDefaultsError, FBeamRequestContext, Context, UGetClientDefaultsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetClientDefaultsComplete, FBeamRequestContext, Context, UGetClientDefaultsRequest*, Request);

using FGetClientDefaultsFullResponse = FBeamFullResponse<UGetClientDefaultsRequest*, URealmConfiguration*>;
DECLARE_DELEGATE_OneParam(FOnGetClientDefaultsFullResponse, FGetClientDefaultsFullResponse);
