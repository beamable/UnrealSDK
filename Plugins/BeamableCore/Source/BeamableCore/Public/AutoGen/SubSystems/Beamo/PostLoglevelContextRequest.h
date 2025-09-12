
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/BeamoV2LogSwitchContextDocument.h"
#include "BeamableCore/Public/AutoGen/BeamoV2EmptyMessage.h"

#include "PostLoglevelContextRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostLoglevelContextRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UBeamoV2LogSwitchContextDocument* Body = {};

	// Beam Base Request Declaration
	UPostLoglevelContextRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make PostLoglevelContext",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Id,_Rules,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostLoglevelContextRequest* Make(FString _ServiceName, FString _RoutingKey, EBeamBeamoV2LogLevel _DefaultLogLevel, FOptionalBeamoV2ObjectId _Id, FOptionalArrayOfBeamoV2LogContextRule _Rules, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostLoglevelContextSuccess, FBeamRequestContext, Context, UPostLoglevelContextRequest*, Request, UBeamoV2EmptyMessage*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostLoglevelContextError, FBeamRequestContext, Context, UPostLoglevelContextRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostLoglevelContextComplete, FBeamRequestContext, Context, UPostLoglevelContextRequest*, Request);

using FPostLoglevelContextFullResponse = FBeamFullResponse<UPostLoglevelContextRequest*, UBeamoV2EmptyMessage*>;
DECLARE_DELEGATE_OneParam(FOnPostLoglevelContextFullResponse, FPostLoglevelContextFullResponse);
