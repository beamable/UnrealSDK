
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/GetProductsResponse.h"

#include "GetSteamProductsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetSteamProductsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Steam Id", Category="Beam")
	int64 SteamId = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetSteamProductsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make GetSteamProducts",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetSteamProductsRequest* Make(int64 _SteamId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetSteamProductsSuccess, FBeamRequestContext, Context, UGetSteamProductsRequest*, Request, UGetProductsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetSteamProductsError, FBeamRequestContext, Context, UGetSteamProductsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetSteamProductsComplete, FBeamRequestContext, Context, UGetSteamProductsRequest*, Request);

using FGetSteamProductsFullResponse = FBeamFullResponse<UGetSteamProductsRequest*, UGetProductsResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetSteamProductsFullResponse, FGetSteamProductsFullResponse);
