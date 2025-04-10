
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/UploadRequests.h"
#include "BeamableCore/Public/AutoGen/CloudsavingBasicManifest.h"

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
	UUploadRequests* Body = {};

	// Beam Base Request Declaration
	UPutDataCommitManifestRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Cloudsaving|Utils|Make/Break", DisplayName="Make PutDataCommitManifest",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_PlayerId,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutDataCommitManifestRequest* Make(TArray<UUploadRequestBody*> _Request, FOptionalInt64 _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutDataCommitManifestSuccess, FBeamRequestContext, Context, UPutDataCommitManifestRequest*, Request, UCloudsavingBasicManifest*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutDataCommitManifestError, FBeamRequestContext, Context, UPutDataCommitManifestRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutDataCommitManifestComplete, FBeamRequestContext, Context, UPutDataCommitManifestRequest*, Request);

using FPutDataCommitManifestFullResponse = FBeamFullResponse<UPutDataCommitManifestRequest*, UCloudsavingBasicManifest*>;
DECLARE_DELEGATE_OneParam(FOnPutDataCommitManifestFullResponse, FPutDataCommitManifestFullResponse);
