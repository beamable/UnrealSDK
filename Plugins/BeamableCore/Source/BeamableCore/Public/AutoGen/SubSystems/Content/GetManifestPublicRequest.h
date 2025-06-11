
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamContentManifestId.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/ClientManifestResponse.h"

#include "GetManifestPublicRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetManifestPublicRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FOptionalBeamContentManifestId Id = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Uid", Category="Beam")
	FOptionalString Uid = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetManifestPublicRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Content|Utils|Make/Break", DisplayName="Make GetManifestPublic",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Id,_Uid,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetManifestPublicRequest* Make(FOptionalBeamContentManifestId _Id, FOptionalString _Uid, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetManifestPublicSuccess, FBeamRequestContext, Context, UGetManifestPublicRequest*, Request, UClientManifestResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetManifestPublicError, FBeamRequestContext, Context, UGetManifestPublicRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetManifestPublicComplete, FBeamRequestContext, Context, UGetManifestPublicRequest*, Request);

using FGetManifestPublicFullResponse = FBeamFullResponse<UGetManifestPublicRequest*, UClientManifestResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetManifestPublicFullResponse, FGetManifestPublicFullResponse);
