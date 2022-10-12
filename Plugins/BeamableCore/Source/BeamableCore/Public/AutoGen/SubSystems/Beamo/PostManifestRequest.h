
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UPostManifestRequestBody* Body;

	// Beam Base Request Declaration
	UPostManifestRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Comments,_bAutoDeploy,_StorageReferences,Outer"))
	static UPostManifestRequest* MakePostManifestRequest(TArray<UServiceReference*> _Manifest, FOptionalString _Comments, FOptionalBool _bAutoDeploy, FOptionalArrayOfServiceStorageReference _StorageReferences, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostManifestSuccess, FBeamRequestContext, Context, UPostManifestRequest*, Request, UPostManifestResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostManifestError, FBeamRequestContext, Context, UPostManifestRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostManifestComplete, FBeamRequestContext, Context, UPostManifestRequest*, Request);

using FPostManifestFullResponse = FBeamFullResponse<UPostManifestRequest*, UPostManifestResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostManifestFullResponse, FPostManifestFullResponse);
