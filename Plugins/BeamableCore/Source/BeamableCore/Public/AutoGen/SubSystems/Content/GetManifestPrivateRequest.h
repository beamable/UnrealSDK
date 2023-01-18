
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "AutoGen/Optionals/OptionalBeamContentManifestId.h"
#include "AutoGen/ClientManifestCsvResponse.h"

#include "GetManifestPrivateRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetManifestPrivateRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FOptionalBeamContentManifestId Id;

	// Body Params
	

	// Beam Base Request Declaration
	UGetManifestPrivateRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Content", DisplayName="Beam - Make GetManifestPrivate",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Id,RequestOwner"))
	static UGetManifestPrivateRequest* Make(FOptionalBeamContentManifestId _Id, UObject* RequestOwner);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetManifestPrivateSuccess, FBeamRequestContext, Context, UGetManifestPrivateRequest*, Request, UClientManifestCsvResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetManifestPrivateError, FBeamRequestContext, Context, UGetManifestPrivateRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetManifestPrivateComplete, FBeamRequestContext, Context, UGetManifestPrivateRequest*, Request);

using FGetManifestPrivateFullResponse = FBeamFullResponse<UGetManifestPrivateRequest*, UClientManifestCsvResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetManifestPrivateFullResponse, FGetManifestPrivateFullResponse);
