
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/GetTemplatesResponse.h"

#include "BasicBeamoGetTemplatesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicBeamoGetTemplatesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UBasicBeamoGetTemplatesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BasicBeamoGetTemplates",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicBeamoGetTemplatesRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicBeamoGetTemplatesSuccess, FBeamRequestContext, Context, UBasicBeamoGetTemplatesRequest*, Request, UGetTemplatesResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicBeamoGetTemplatesError, FBeamRequestContext, Context, UBasicBeamoGetTemplatesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicBeamoGetTemplatesComplete, FBeamRequestContext, Context, UBasicBeamoGetTemplatesRequest*, Request);

using FBasicBeamoGetTemplatesFullResponse = FBeamFullResponse<UBasicBeamoGetTemplatesRequest*, UGetTemplatesResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicBeamoGetTemplatesFullResponse, FBasicBeamoGetTemplatesFullResponse);
