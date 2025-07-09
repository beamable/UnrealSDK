
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/ConnectionString.h"

#include "BasicBeamoGetStorageConnectionRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicBeamoGetStorageConnectionRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UBasicBeamoGetStorageConnectionRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BasicBeamoGetStorageConnection",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicBeamoGetStorageConnectionRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicBeamoGetStorageConnectionSuccess, FBeamRequestContext, Context, UBasicBeamoGetStorageConnectionRequest*, Request, UConnectionString*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicBeamoGetStorageConnectionError, FBeamRequestContext, Context, UBasicBeamoGetStorageConnectionRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicBeamoGetStorageConnectionComplete, FBeamRequestContext, Context, UBasicBeamoGetStorageConnectionRequest*, Request);

using FBasicBeamoGetStorageConnectionFullResponse = FBeamFullResponse<UBasicBeamoGetStorageConnectionRequest*, UConnectionString*>;
DECLARE_DELEGATE_OneParam(FOnBasicBeamoGetStorageConnectionFullResponse, FBasicBeamoGetStorageConnectionFullResponse);
