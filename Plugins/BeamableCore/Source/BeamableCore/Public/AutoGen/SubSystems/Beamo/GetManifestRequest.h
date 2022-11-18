
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Archived", Category="Beam")
	FOptionalBool bArchived;

	// Body Params
	

	// Beam Base Request Declaration
	UGetManifestRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Beamo", DisplayName="Beam - Make GetManifest",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bArchived,RequestOwner"))
	static UGetManifestRequest* Make(FString _Id, FOptionalBool _bArchived, UObject* RequestOwner);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetManifestSuccess, FBeamRequestContext, Context, UGetManifestRequest*, Request, UGetManifestResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetManifestError, FBeamRequestContext, Context, UGetManifestRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetManifestComplete, FBeamRequestContext, Context, UGetManifestRequest*, Request);

using FGetManifestFullResponse = FBeamFullResponse<UGetManifestRequest*, UGetManifestResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetManifestFullResponse, FGetManifestFullResponse);
