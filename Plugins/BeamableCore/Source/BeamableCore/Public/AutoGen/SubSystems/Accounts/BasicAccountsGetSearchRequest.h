
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/AccountSearchResponse.h"

#include "BasicAccountsGetSearchRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicAccountsGetSearchRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Query", Category="Beam")
	FString Query = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Page", Category="Beam")
	int32 Page = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Pagesize", Category="Beam")
	int32 Pagesize = {};

	// Body Params
	

	// Beam Base Request Declaration
	UBasicAccountsGetSearchRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make BasicAccountsGetSearch",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicAccountsGetSearchRequest* Make(FString _Query, int32 _Page, int32 _Pagesize, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicAccountsGetSearchSuccess, FBeamRequestContext, Context, UBasicAccountsGetSearchRequest*, Request, UAccountSearchResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicAccountsGetSearchError, FBeamRequestContext, Context, UBasicAccountsGetSearchRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicAccountsGetSearchComplete, FBeamRequestContext, Context, UBasicAccountsGetSearchRequest*, Request);

using FBasicAccountsGetSearchFullResponse = FBeamFullResponse<UBasicAccountsGetSearchRequest*, UAccountSearchResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicAccountsGetSearchFullResponse, FBasicAccountsGetSearchFullResponse);
