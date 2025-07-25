
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/BeamoV2ConnectionStringResponse.h"

#include "ApiBeamoGetStorageConnectionRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiBeamoGetStorageConnectionRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UApiBeamoGetStorageConnectionRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make ApiBeamoGetStorageConnection",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiBeamoGetStorageConnectionRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiBeamoGetStorageConnectionSuccess, FBeamRequestContext, Context, UApiBeamoGetStorageConnectionRequest*, Request, UBeamoV2ConnectionStringResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiBeamoGetStorageConnectionError, FBeamRequestContext, Context, UApiBeamoGetStorageConnectionRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiBeamoGetStorageConnectionComplete, FBeamRequestContext, Context, UApiBeamoGetStorageConnectionRequest*, Request);

using FApiBeamoGetStorageConnectionFullResponse = FBeamFullResponse<UApiBeamoGetStorageConnectionRequest*, UBeamoV2ConnectionStringResponse*>;
DECLARE_DELEGATE_OneParam(FOnApiBeamoGetStorageConnectionFullResponse, FApiBeamoGetStorageConnectionFullResponse);
