
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/CustomerActorAliasAvailableResponse.h"

#include "GetAliasesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetAliasesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Alias", Category="Beam")
	FString Alias = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetAliasesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make GetAliases",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetAliasesRequest* Make(FString _Alias, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAliasesSuccess, FBeamRequestContext, Context, UGetAliasesRequest*, Request, UCustomerActorAliasAvailableResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAliasesError, FBeamRequestContext, Context, UGetAliasesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetAliasesComplete, FBeamRequestContext, Context, UGetAliasesRequest*, Request);

using FGetAliasesFullResponse = FBeamFullResponse<UGetAliasesRequest*, UCustomerActorAliasAvailableResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetAliasesFullResponse, FGetAliasesFullResponse);
