
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"



#include "AutoGen/AccountSearchResponse.h"

#include "BasicAccountsGetSearchRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicAccountsGetSearchRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Query")
	FString Query;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Page")
	int32 Page;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Pagesize")
	int32 Pagesize;

	// Body Params
	

	// Beam Base Request Declaration
	UBasicAccountsGetSearchRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UBasicAccountsGetSearchRequest* MakeBasicAccountsGetSearchRequest(FString _Query, int32 _Page, int32 _Pagesize, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicAccountsGetSearchSuccess, FBeamRequestContext, Context, UBasicAccountsGetSearchRequest*, Request, UAccountSearchResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicAccountsGetSearchError, FBeamRequestContext, Context, UBasicAccountsGetSearchRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicAccountsGetSearchComplete, FBeamRequestContext, Context, UBasicAccountsGetSearchRequest*, Request);

using FBasicAccountsGetSearchFullResponse = FBeamFullResponse<UBasicAccountsGetSearchRequest*, UAccountSearchResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicAccountsGetSearchFullResponse, FBasicAccountsGetSearchFullResponse);
