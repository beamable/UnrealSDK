
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "AutoGen/Optionals/OptionalBeamContentManifestId.h"
#include "AutoGen/ContentBasicManifestChecksum.h"

#include "GetManifestChecksumRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetManifestChecksumRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FOptionalBeamContentManifestId Id;

	// Body Params
	

	// Beam Base Request Declaration
	UGetManifestChecksumRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Content", DisplayName="Beam - Make GetManifestChecksum",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Id,RequestOwner"))
	static UGetManifestChecksumRequest* Make(FOptionalBeamContentManifestId _Id, UObject* RequestOwner);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetManifestChecksumSuccess, FBeamRequestContext, Context, UGetManifestChecksumRequest*, Request, UContentBasicManifestChecksum*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetManifestChecksumError, FBeamRequestContext, Context, UGetManifestChecksumRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetManifestChecksumComplete, FBeamRequestContext, Context, UGetManifestChecksumRequest*, Request);

using FGetManifestChecksumFullResponse = FBeamFullResponse<UGetManifestChecksumRequest*, UContentBasicManifestChecksum*>;
DECLARE_DELEGATE_OneParam(FOnGetManifestChecksumFullResponse, FGetManifestChecksumFullResponse);