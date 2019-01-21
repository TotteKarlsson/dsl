
{*******************************************************}
{                                                       }
{       Borland Delphi Visual Component Library         }
{                                                       }
{  Copyright (c) 2001-2002 Borland Software Corporation }
{                                                       }
{*******************************************************}

unit AMHelp;

interface

uses Classes, ActnList, ActnMan;

type
  TAMHelp = class(TComponent)
  private
    FAction: TCustomAction;
    FActionManager: TCustomActionManager;
    FCaption: string;
    FCompareProc: TActionProc;
    FFoundClient: TActionClientItem;
    procedure CompareCaption(AClient: TActionClient);
    procedure CompareAction(AClient: TActionClient);
    function FindItem: TActionClientItem;
  protected
    procedure FindClient(AClient: TActionClient);
    procedure Notification(AComponent: TComponent; Operation: TOperation);
      override;
  public
    function AddAction(AnAction: TCustomAction; AClient: TActionClient;
      After: Boolean = True): TActionClientItem;
    function AddCategory(ACategory: string; AClient: TActionClient;
      After: Boolean = True): TActionClientItem;
    function AddSeparator(AnItem: TActionClientItem; After: Boolean = True): TActionClientItem;
    procedure DeleteActionItems(Actions: array of TCustomAction);
    procedure DeleteItem(Caption: string);
    function FindItemByCaption(ACaption: string): TActionClientItem;
    function FindItemByAction(Action: TCustomAction): TActionClientItem;
  published
    property ActionManager: TCustomActionManager read FActionManager
      write FActionManager;
  end;

procedure Register;

implementation

uses SysUtils;

{ TAMHelp }

{ AddAction adds AnAction to an ActionBand either before or after
  AClient.  Use this method to insert a new action into an existing
  ActionBand.  Use one of the FindItemxxx methods to locate the position
  at which you want to insert the new item. }
function TAMHelp.AddAction(AnAction: TCustomAction;
  AClient: TActionClient; After: Boolean): TActionClientItem;
begin
  Result := nil;
  if (FActionManager = nil) or (AClient = nil) or
     (AClient.Collection = nil) then exit;
  Result := TActionClientItem(AClient.Collection.Add);
  Result.Index := AClient.Index + Integer(After);
  Result.Action := AnAction;
end;

type
  TActionManagerClass = class(TCustomActionManager);
  TActionArray = array of TContainedAction;

function AddActions(var Actions: TActionArray;
  ActionList: TCustomActionList; ACategory: string): Integer;
var
  I: Integer;
begin
  Result := Length(Actions);
  if ActionList = nil then exit;
  SetLength(Actions, Result + ActionList.ActionCount);
  for I := 0 to ActionList.ActionCount - 1 do
    if CompareText(ActionList[I].Category, ACategory) = 0 then
    begin
      Actions[Result] := ActionList[I];
      Inc(Result);
    end;
  SetLength(Actions, Result);
end;

{ AddCategory adds all of the actions from ACategory to an ActionBand
  inserting it either before or after the AClient item.  }
function TAMHelp.AddCategory(ACategory: string;
  AClient: TActionClient; After: Boolean): TActionClientItem;
var
  I: Integer;
  Actions: TActionArray;
begin
  Result := nil;
  if (FActionManager = nil) or (AClient = nil) then exit;
  AddActions(Actions, FActionManager, ACategory);
  for I := 0 to FActionManager.LinkedActionLists.Count - 1 do
    AddActions(Actions, FActionManager.LinkedActionLists[I].ActionList, ACategory);
  with AClient as TActionClient do
  begin
    Result := TActionManagerClass(ActionManager).GetActionClientItemClass.Create(nil);
    Result.Caption := ACategory;
    Result.Collection := AClient.Collection;
    Result.Index := AClient.Index + Integer(After);
    for I := 0 to Length(Actions) - 1 do
      Result.Items.Add.Action := Actions[I];

    Result.Control.Enabled := True;
  end;
end;

{ AddSeparator adds a separator to an ActionBand following AnItem.  Use
  the FindItemxxx methods to locate the item you want to instert a
  separator either before or after. }
function TAMHelp.AddSeparator(
  AnItem: TActionClientItem; After: Boolean = True): TActionClientItem;
begin
  Result := nil;
  if (FActionManager = nil) or (AnItem = nil) or
     (AnItem.ActionClients = nil) then exit;
  Result := AnItem.ActionClients.Add;
  Result.Caption := '|';
  Result.Index := AnItem.Index + Integer(After);
end;

procedure TAMHelp.CompareAction(AClient: TActionClient);
begin
  if AClient is TActionClientItem then
    with AClient as TActionClientItem do
      if Action = FAction then
        FFoundClient := TActionClientItem(AClient);
end;

procedure TAMHelp.CompareCaption(AClient: TActionClient);
begin
  if AClient is TActionClientItem then
    with AClient as TActionClientItem do
      if CompareText(Caption, FCaption) = 0 then
        FFoundClient := TActionClientItem(AClient);
end;

{ DeleteActionItems removes items from the ActionBars collection which are
  linked to the Actions specified. }
procedure TAMHelp.DeleteActionItems(Actions: array of TCustomAction);
var
  I: Integer;
  Item: TActionClientItem;
begin
  if FActionManager = nil then exit;
  for I := Low(Actions) to High(Actions) do
  begin
    Item := FindItemByAction(Actions[I]);
    if Assigned(Item) then
      Item.Free;
  end;
end;

{ DeleteItem deletes an ActionBand item after locating it based on it's
  Caption. }
procedure TAMHelp.DeleteItem(Caption: string);
var
  Item: TActionClientItem;
begin
  FFoundClient := nil;
  FCaption := Caption;
  Item := FindItemByCaption(Caption);
  if Assigned(Item) then
    Item.Free;
end;

procedure TAMHelp.FindClient(AClient: TActionClient);
begin
  if Assigned(AClient) and Assigned(FCompareProc) and
     Assigned(FFoundClient) then exit;  // Only find the first occurance
    FCompareProc(AClient);
end;

function TAMHelp.FindItem: TActionClientItem;
begin
  Result := nil;
  if FActionManager = nil then exit;
  FFoundClient := nil;
  ActionManager.ActionBars.IterateClients(ActionManager.ActionBars, FindClient);
  Result := FFoundClient;
end;

{ FindItemByAction takes an Action and returns the first item that is linked
  to that action. }
function TAMHelp.FindItemByAction(
  Action: TCustomAction): TActionClientItem;
begin
  FCompareProc := CompareAction;
  FAction := Action;
  Result := FindItem;
end;

{ FindItemByCaption takes ACaption and returns the first item with a matching
  caption. }
function TAMHelp.FindItemByCaption(
  ACaption: string): TActionClientItem;
begin
  FCompareProc := CompareCaption;
  FCaption := ACaption;
  Result := FindItem;
end;

procedure TAMHelp.Notification(AComponent: TComponent;
  Operation: TOperation);
begin
  inherited;
  if (Operation = opRemove) and (FActionManager = AComponent) then
    FActionManager := nil; 
end;

procedure Register;
begin
  RegisterComponents('mtkComponents', [TAMHelp]);
end;

end.
