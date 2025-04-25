
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/ArchiveOrUnarchiveManifestsRequestBody.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#include "PostManifestsUnarchiveRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostManifestsUnarchiveRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UArchiveOrUnarchiveManifestsRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostManifestsUnarchiveRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Content|Utils|Make/Break", DisplayName="Make PostManifestsUnarchive",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostManifestsUnarchiveRequest* Make(TArray<FBeamContentManifestId> _ManifestIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostManifestsUnarchiveSuccess, FBeamRequestContext, Context, UPostManifestsUnarchiveRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostManifestsUnarchiveError, FBeamRequestContext, Context, UPostManifestsUnarchiveRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostManifestsUnarchiveComplete, FBeamRequestContext, Context, UPostManifestsUnarchiveRequest*, Request);

using FPostManifestsUnarchiveFullResponse = FBeamFullResponse<UPostManifestsUnarchiveRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostManifestsUnarchiveFullResponse, FPostManifestsUnarchiveFullResponse);
