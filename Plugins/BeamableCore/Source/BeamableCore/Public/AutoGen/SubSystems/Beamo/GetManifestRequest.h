
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/GetManifestResponse.h"

#include "GetManifestRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetManifestRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Archived")
	FOptionalBool bArchived;

	// Body Params
	

	// Beam Base Request Declaration
	UGetManifestRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_bArchived,Outer"))
	static UGetManifestRequest* MakeGetManifestRequest(FString _Id, FOptionalBool _bArchived, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetManifestSuccess, FBeamRequestContext, Context, UGetManifestRequest*, Request, UGetManifestResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetManifestError, FBeamRequestContext, Context, UGetManifestRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetManifestComplete, FBeamRequestContext, Context, UGetManifestRequest*, Request);

using FGetManifestFullResponse = FBeamFullResponse<UGetManifestRequest*, UGetManifestResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetManifestFullResponse, FGetManifestFullResponse);
