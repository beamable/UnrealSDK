
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"
#include "BeamableCore/Public/AutoGen/GetCatalogResponse.h"

#include "GetCatalogRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetCatalogRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Version", Category="Beam")
	FOptionalInt64 Version = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetCatalogRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make GetCatalog",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Version,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetCatalogRequest* Make(FOptionalInt64 _Version, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCatalogSuccess, FBeamRequestContext, Context, UGetCatalogRequest*, Request, UGetCatalogResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCatalogError, FBeamRequestContext, Context, UGetCatalogRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetCatalogComplete, FBeamRequestContext, Context, UGetCatalogRequest*, Request);

using FGetCatalogFullResponse = FBeamFullResponse<UGetCatalogRequest*, UGetCatalogResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetCatalogFullResponse, FGetCatalogFullResponse);
