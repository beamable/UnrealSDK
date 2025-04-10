
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/MailResponse.h"

#include "BasicMailGetMailRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicMailGetMailRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Mid", Category="Beam")
	int64 Mid = {};

	// Body Params
	

	// Beam Base Request Declaration
	UBasicMailGetMailRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Mail|Utils|Make/Break", DisplayName="Make BasicMailGetMail",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicMailGetMailRequest* Make(int64 _Mid, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicMailGetMailSuccess, FBeamRequestContext, Context, UBasicMailGetMailRequest*, Request, UMailResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicMailGetMailError, FBeamRequestContext, Context, UBasicMailGetMailRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicMailGetMailComplete, FBeamRequestContext, Context, UBasicMailGetMailRequest*, Request);

using FBasicMailGetMailFullResponse = FBeamFullResponse<UBasicMailGetMailRequest*, UMailResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicMailGetMailFullResponse, FBasicMailGetMailFullResponse);
