
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/CommitImageRequestBody.h"
#include "BeamableCore/Public/AutoGen/LambdaResponse.h"

#include "PutImageCommitRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutImageCommitRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCommitImageRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutImageCommitRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make PutImageCommit",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutImageCommitRequest* Make(UBeamoBasicReference* _Service, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutImageCommitSuccess, FBeamRequestContext, Context, UPutImageCommitRequest*, Request, ULambdaResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutImageCommitError, FBeamRequestContext, Context, UPutImageCommitRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutImageCommitComplete, FBeamRequestContext, Context, UPutImageCommitRequest*, Request);

using FPutImageCommitFullResponse = FBeamFullResponse<UPutImageCommitRequest*, ULambdaResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutImageCommitFullResponse, FPutImageCommitFullResponse);
