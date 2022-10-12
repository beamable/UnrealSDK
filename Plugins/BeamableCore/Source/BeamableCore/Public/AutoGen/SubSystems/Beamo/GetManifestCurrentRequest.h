
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/GetCurrentManifestResponse.h"

#include "GetManifestCurrentRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetManifestCurrentRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Archived")
	FOptionalBool bArchived;

	// Body Params
	

	// Beam Base Request Declaration
	UGetManifestCurrentRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_bArchived,Outer"))
	static UGetManifestCurrentRequest* MakeGetManifestCurrentRequest(FOptionalBool _bArchived, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetManifestCurrentSuccess, FBeamRequestContext, Context, UGetManifestCurrentRequest*, Request, UGetCurrentManifestResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetManifestCurrentError, FBeamRequestContext, Context, UGetManifestCurrentRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetManifestCurrentComplete, FBeamRequestContext, Context, UGetManifestCurrentRequest*, Request);

using FGetManifestCurrentFullResponse = FBeamFullResponse<UGetManifestCurrentRequest*, UGetCurrentManifestResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetManifestCurrentFullResponse, FGetManifestCurrentFullResponse);
