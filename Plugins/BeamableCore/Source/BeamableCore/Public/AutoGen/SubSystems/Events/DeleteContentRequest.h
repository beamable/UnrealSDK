
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "AutoGen/CommonResponse.h"

#include "DeleteContentRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteContentRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UDeleteContentRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Events", DisplayName="Beam - Make DeleteContent",  meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UDeleteContentRequest* Make(int64 _ObjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteContentSuccess, FBeamRequestContext, Context, UDeleteContentRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteContentError, FBeamRequestContext, Context, UDeleteContentRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteContentComplete, FBeamRequestContext, Context, UDeleteContentRequest*, Request);

using FDeleteContentFullResponse = FBeamFullResponse<UDeleteContentRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteContentFullResponse, FDeleteContentFullResponse);
