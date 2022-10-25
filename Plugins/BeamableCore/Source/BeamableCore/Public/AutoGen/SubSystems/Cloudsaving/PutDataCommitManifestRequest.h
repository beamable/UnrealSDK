
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "AutoGen/UploadRequests.h"
#include "AutoGen/Manifest.h"

#include "PutDataCommitManifestRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutDataCommitManifestRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UUploadRequests* Body;

	// Beam Base Request Declaration
	UPutDataCommitManifestRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Cloudsaving", DisplayName="Beam - Make PutDataCommitManifest",  meta=(DefaultToSelf="Outer", AdvancedDisplay="_PlayerId,Outer"))
	static UPutDataCommitManifestRequest* Make(TArray<UUploadRequestBody*> _Request, FOptionalInt64 _PlayerId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutDataCommitManifestSuccess, FBeamRequestContext, Context, UPutDataCommitManifestRequest*, Request, UManifest*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutDataCommitManifestError, FBeamRequestContext, Context, UPutDataCommitManifestRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutDataCommitManifestComplete, FBeamRequestContext, Context, UPutDataCommitManifestRequest*, Request);

using FPutDataCommitManifestFullResponse = FBeamFullResponse<UPutDataCommitManifestRequest*, UManifest*>;
DECLARE_DELEGATE_OneParam(FOnPutDataCommitManifestFullResponse, FPutDataCommitManifestFullResponse);
