
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/BeamoV2GetManifestsResponse.h"

#include "ApiBeamoGetManifestsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiBeamoGetManifestsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Offset", Category="Beam")
	FOptionalInt32 Offset = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Limit", Category="Beam")
	FOptionalInt32 Limit = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Archived", Category="Beam")
	FOptionalBool bArchived = {};

	// Body Params
	

	// Beam Base Request Declaration
	UApiBeamoGetManifestsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make ApiBeamoGetManifests",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Offset,_Limit,_bArchived,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiBeamoGetManifestsRequest* Make(FOptionalInt32 _Offset, FOptionalInt32 _Limit, FOptionalBool _bArchived, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiBeamoGetManifestsSuccess, FBeamRequestContext, Context, UApiBeamoGetManifestsRequest*, Request, UBeamoV2GetManifestsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiBeamoGetManifestsError, FBeamRequestContext, Context, UApiBeamoGetManifestsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiBeamoGetManifestsComplete, FBeamRequestContext, Context, UApiBeamoGetManifestsRequest*, Request);

using FApiBeamoGetManifestsFullResponse = FBeamFullResponse<UApiBeamoGetManifestsRequest*, UBeamoV2GetManifestsResponse*>;
DECLARE_DELEGATE_OneParam(FOnApiBeamoGetManifestsFullResponse, FApiBeamoGetManifestsFullResponse);
