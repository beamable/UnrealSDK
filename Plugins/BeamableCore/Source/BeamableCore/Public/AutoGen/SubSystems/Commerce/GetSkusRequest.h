
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"
#include "BeamableCore/Public/AutoGen/GetSKUsResponse.h"

#include "GetSkusRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetSkusRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Version", Category="Beam")
	FOptionalInt64 Version = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetSkusRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make GetSkus",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Version,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetSkusRequest* Make(FOptionalInt64 _Version, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetSkusSuccess, FBeamRequestContext, Context, UGetSkusRequest*, Request, UGetSKUsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetSkusError, FBeamRequestContext, Context, UGetSkusRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetSkusComplete, FBeamRequestContext, Context, UGetSkusRequest*, Request);

using FGetSkusFullResponse = FBeamFullResponse<UGetSkusRequest*, UGetSKUsResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetSkusFullResponse, FGetSkusFullResponse);
