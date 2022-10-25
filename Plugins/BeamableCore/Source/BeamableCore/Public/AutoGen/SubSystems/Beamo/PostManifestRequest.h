
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "AutoGen/PostManifestRequestBody.h"
#include "AutoGen/PostManifestResponse.h"

#include "PostManifestRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostManifestRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UPostManifestRequestBody* Body;

	// Beam Base Request Declaration
	UPostManifestRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Beamo", DisplayName="Beam - Make PostManifest",  meta=(DefaultToSelf="Outer", AdvancedDisplay="_bAutoDeploy,_Comments,_StorageReferences,Outer"))
	static UPostManifestRequest* Make(TArray<UServiceReference*> _Manifest, FOptionalBool _bAutoDeploy, FOptionalString _Comments, FOptionalArrayOfServiceStorageReference _StorageReferences, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostManifestSuccess, FBeamRequestContext, Context, UPostManifestRequest*, Request, UPostManifestResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostManifestError, FBeamRequestContext, Context, UPostManifestRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostManifestComplete, FBeamRequestContext, Context, UPostManifestRequest*, Request);

using FPostManifestFullResponse = FBeamFullResponse<UPostManifestRequest*, UPostManifestResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostManifestFullResponse, FPostManifestFullResponse);
