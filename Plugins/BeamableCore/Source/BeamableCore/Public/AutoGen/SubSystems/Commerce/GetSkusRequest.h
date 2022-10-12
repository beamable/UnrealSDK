
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/GetSKUsResponse.h"

#include "GetSkusRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetSkusRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Version")
	FOptionalInt64 Version;

	// Body Params
	

	// Beam Base Request Declaration
	UGetSkusRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Version,Outer"))
	static UGetSkusRequest* MakeGetSkusRequest(FOptionalInt64 _Version, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetSkusSuccess, FBeamRequestContext, Context, UGetSkusRequest*, Request, UGetSKUsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetSkusError, FBeamRequestContext, Context, UGetSkusRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetSkusComplete, FBeamRequestContext, Context, UGetSkusRequest*, Request);

using FGetSkusFullResponse = FBeamFullResponse<UGetSkusRequest*, UGetSKUsResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetSkusFullResponse, FGetSkusFullResponse);