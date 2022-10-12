
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/GetActiveOffersResponse.h"

#include "GetCommerceRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetCommerceRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Scope")
	FOptionalString Scope;

	// Body Params
	

	// Beam Base Request Declaration
	UGetCommerceRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Scope,Outer"))
	static UGetCommerceRequest* MakeGetCommerceRequest(int64 _ObjectId, FOptionalString _Scope, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCommerceSuccess, FBeamRequestContext, Context, UGetCommerceRequest*, Request, UGetActiveOffersResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCommerceError, FBeamRequestContext, Context, UGetCommerceRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetCommerceComplete, FBeamRequestContext, Context, UGetCommerceRequest*, Request);

using FGetCommerceFullResponse = FBeamFullResponse<UGetCommerceRequest*, UGetActiveOffersResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetCommerceFullResponse, FGetCommerceFullResponse);
