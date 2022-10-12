
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/AccountsBasicAccount.h"

#include "GetFindRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetFindRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Query")
	FString Query;

	// Body Params
	

	// Beam Base Request Declaration
	UGetFindRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetFindRequest* MakeGetFindRequest(FString _Query, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetFindSuccess, FBeamRequestContext, Context, UGetFindRequest*, Request, UAccountsBasicAccount*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetFindError, FBeamRequestContext, Context, UGetFindRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetFindComplete, FBeamRequestContext, Context, UGetFindRequest*, Request);

using FGetFindFullResponse = FBeamFullResponse<UGetFindRequest*, UAccountsBasicAccount*>;
DECLARE_DELEGATE_OneParam(FOnGetFindFullResponse, FGetFindFullResponse);
