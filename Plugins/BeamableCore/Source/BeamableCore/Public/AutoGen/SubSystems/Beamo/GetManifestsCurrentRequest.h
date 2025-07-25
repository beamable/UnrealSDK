
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/BeamoV2Manifest.h"

#include "GetManifestsCurrentRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetManifestsCurrentRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Archived", Category="Beam")
	FOptionalBool bArchived = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetManifestsCurrentRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make GetManifestsCurrent",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bArchived,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetManifestsCurrentRequest* Make(FOptionalBool _bArchived, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetManifestsCurrentSuccess, FBeamRequestContext, Context, UGetManifestsCurrentRequest*, Request, UBeamoV2Manifest*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetManifestsCurrentError, FBeamRequestContext, Context, UGetManifestsCurrentRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetManifestsCurrentComplete, FBeamRequestContext, Context, UGetManifestsCurrentRequest*, Request);

using FGetManifestsCurrentFullResponse = FBeamFullResponse<UGetManifestsCurrentRequest*, UBeamoV2Manifest*>;
DECLARE_DELEGATE_OneParam(FOnGetManifestsCurrentFullResponse, FGetManifestsCurrentFullResponse);
