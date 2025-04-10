
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/GetActiveOffersResponse.h"

#include "GetCommerceRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetCommerceRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Scope", Category="Beam")
	FOptionalString Scope = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetCommerceRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make GetCommerce",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Scope,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetCommerceRequest* Make(int64 _ObjectId, FOptionalString _Scope, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCommerceSuccess, FBeamRequestContext, Context, UGetCommerceRequest*, Request, UGetActiveOffersResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCommerceError, FBeamRequestContext, Context, UGetCommerceRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetCommerceComplete, FBeamRequestContext, Context, UGetCommerceRequest*, Request);

using FGetCommerceFullResponse = FBeamFullResponse<UGetCommerceRequest*, UGetActiveOffersResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetCommerceFullResponse, FGetCommerceFullResponse);
