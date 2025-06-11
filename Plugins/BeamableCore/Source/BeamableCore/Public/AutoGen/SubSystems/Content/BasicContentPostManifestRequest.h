
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/SaveManifestRequestBody.h"
#include "BeamableCore/Public/AutoGen/ContentBasicManifest.h"

#include "BasicContentPostManifestRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicContentPostManifestRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	USaveManifestRequestBody* Body = {};

	// Beam Base Request Declaration
	UBasicContentPostManifestRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Content|Utils|Make/Break", DisplayName="Make BasicContentPostManifest",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicContentPostManifestRequest* Make(FBeamContentManifestId _Id, TArray<UReferenceSuperset*> _References, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicContentPostManifestSuccess, FBeamRequestContext, Context, UBasicContentPostManifestRequest*, Request, UContentBasicManifest*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicContentPostManifestError, FBeamRequestContext, Context, UBasicContentPostManifestRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicContentPostManifestComplete, FBeamRequestContext, Context, UBasicContentPostManifestRequest*, Request);

using FBasicContentPostManifestFullResponse = FBeamFullResponse<UBasicContentPostManifestRequest*, UContentBasicManifest*>;
DECLARE_DELEGATE_OneParam(FOnBasicContentPostManifestFullResponse, FBasicContentPostManifestFullResponse);
